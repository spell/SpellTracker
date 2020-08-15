#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "ItemPickerDialog.h"

#include <iostream>

#include <QDir>
#include <QXmlStreamReader>
#include <QDockWidget>

MainWindow::MainWindow(QWidget* parent)
		: QMainWindow(parent),
		  ui(new Ui::MainWindow),
		  settingsDialog(new SettingsDialog(this)),
		  layoutModel(new ItemLayoutModel(&itemDictionary, &itemLevels, &strings, this)),
		  itemTracker(new ItemTrackerView(this)),
		  popoutWindow(new StreamerPopoutWindow(layoutModel, iconSet, this)) {
	ui->setupUi(this);
	centralWidget()->layout()->addWidget(itemTracker);
	itemTracker->setModel(layoutModel);
	ui->logicTrackerScrollArea->hide();

	connect(itemTracker, &ItemTrackerView::itemPrimaryClicked, this, &MainWindow::itemTracker_clicked);
	connect(itemTracker, &ItemTrackerView::itemSecondaryClicked, layoutModel, &ItemLayoutModel::itemTextToggled);
	connect(this, &MainWindow::itemUpgradeLevelChanged, layoutModel, &ItemLayoutModel::upgradeLevelChanged);
	connect(ui->actionShow_Item_Tracker, &QAction::triggered, itemTracker, &QWidget::setVisible);
	connect(ui->actionShow_Logic_Tracker, &QAction::triggered, ui->logicTrackerScrollArea, &QScrollArea::setVisible);
	connect(ui->actionShow_Streaming_Popout, &QAction::triggered, popoutWindow, &QWidget::setVisible);
	connect(ui->actionSettings, &QAction::triggered, settingsDialog, &SettingsDialog::show);

	// Connect settings dialog stuff
	connect(settingsDialog, &SettingsDialog::iconSpacingValueChanged, itemTracker, &ItemTrackerView::setIconSpacing);
	connect(settingsDialog, &SettingsDialog::iconScaleValueChanged, itemTracker, &ItemTrackerView::setIconScale);

	// Scan game data folder
	QDir dataDirectory("gamedata");
	QStringList gameDataFiles = dataDirectory.entryList(QStringList() << "*.xml", QDir::Files);

	for (const auto& entry: gameDataFiles) {
		QFile file(dataDirectory.filePath(entry));

		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			statusBar()->showMessage(QString{"Couldn't open file: %1"}.arg(file.fileName()));
			continue;
		}

		QXmlStreamReader xml(&file);

		xml.readNextStartElement();
		if (!xml.hasError() && xml.name() == "Data") {
			if (xml.attributes().hasAttribute("name")) {
				auto name = xml.attributes().value("name");

				// Create a new action:
				auto* openAct = new QAction(name.toString(), this);
				connect(openAct, &QAction::triggered, this, [=]() {
					loadDataFile(dataDirectory.filePath(entry));
				});

				ui->menuGame_Data->addAction(openAct);
			} else {
				statusBar()->showMessage(QString{"Game data XML is malformed, missing required 'name' attribute"});
				continue;
			}
		} else {
			statusBar()->showMessage(QString{"Couldn't read game data XML file: %1"}.arg(xml.errorString()));
			continue;
		}
	}
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::loadDataFile(const QString& path) {
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		statusBar()->showMessage(QString{"Couldn't open file: %1"}.arg(file.fileName()));
		return;
	}

	QXmlStreamReader xml(&file);
	xml.readNextStartElement();

	if (xml.hasError() || xml.name() != "Data") {
		statusBar()->showMessage(QString{"Couldn't read game data XML fil: %1"}.arg(file.fileName()));
		return;
	}

	if (!xml.attributes().hasAttribute("name")) {
		statusBar()->showMessage(QString{"Game data XML is malformed, missing required 'name' attribute"});
		return;
	}

	auto name = xml.attributes().value("name").toString();
	setWindowTitle(QString{"SpellTracker - %1"}.arg(name));

	// Clear the current tracker out
	clearTracker();

	// Load the icon theme.
	auto iconsFilename = xml.attributes().value("icons").toString();
	loadIconSet(iconsFilename);

	// Read the file in earnest now.
	while (!xml.atEnd()) {
		xml.readNext();

		if (!xml.isEndElement()) {
			if (xml.name() == "Items") {
				parseItems(&xml);
			}

			if (xml.name() == "Strings") {
				parseStrings(&xml);
			}

			if (xml.name() == "Layouts") {
				parseLayouts(&xml);
			}
		}
	}

	if (xml.hasError()) {
		statusBar()->showMessage(QString{"Error while reading data for '%1': %2"}
				                         .arg(name)
				                         .arg(xml.errorString()));
		return;
	}
}

bool MainWindow::loadIconSet(const QString& filename) {
	QDir iconsDirectory("icons");
	iconSet = IconSet(iconsDirectory.filePath(filename));

	// Emit the correct signals here instead!
	itemTracker->setIconSet(iconSet);
	popoutWindow->setIcons(iconSet);

	return true;
}

void MainWindow::clearTracker() {
	itemDictionary.clear();
	itemLevels.clear();
	strings.clear();
	layoutModel->clear();
}

void MainWindow::parseItems(QXmlStreamReader* xml) {
	QString category;

	while (!xml->atEnd()) {
		xml->readNext();

		if (xml->name() == "Items" && xml->isEndElement()) {
			break;
		}

		if (xml->name() == "Category") {
			category = xml->attributes().value("id").toString();
			continue;
		}

		if (xml->name() == "Item" && xml->isStartElement()) {
			parseItem(xml, category);
		}
	}
}

void MainWindow::parseItem(QXmlStreamReader* xml, QStringView category) {
	auto id = xml->attributes().value("id").toString();
	auto name = xml->attributes().value("name").toString();
	auto icon = xml->attributes().value("icon").toInt();

	if (id.isEmpty() || name.isEmpty()) {
		statusBar()->showMessage("Required attributes 'id' and 'name' missing from Item");
		return;
	}

	Item item(id, name, category, icon);

	if (xml->attributes().value("stacking") == "true") {
		item.setMaxCount(xml->attributes().value("max").toInt());
	}

	// Process this one last, as we will be advancing the cursor
	if (xml->attributes().value("progressive") == "true") {
		QStringList upgradeList;

		while (!xml->atEnd()) {
			xml->readNext();

			if (xml->name() == "Item" && xml->isEndElement()) {
				break;
			}

			if (xml->name() == "Upgrade" && xml->isStartElement()) {
				auto upgradeId = xml->attributes().value("id").toString();

				if (id.isEmpty()) {
					statusBar()->showMessage("Required attribute 'id' missing from Upgrade");
					continue;
				}

				upgradeList.append(upgradeId);
			}
		}

		item.setUpgrades(upgradeList);
	}

	// Add the item into the dictionary
	itemDictionary.insert(id, item);
	itemLevels.insert(id, 0);
}

void MainWindow::parseLayouts(QXmlStreamReader* xml) {
	while (!xml->atEnd() && xml->readNextStartElement()) {
		if (xml->name() == "Layout") {
			// Remember who this layout is for
			auto layoutFor = xml->attributes().value("for").toString();

			while (!xml->atEnd() && xml->readNext()) {
				if (xml->name() == "Icon" && xml->isStartElement()) {
					ItemLayoutObject object(xml->attributes().value("id").toString());
					object.setText(xml->attributes().value("text").toString());
					object.setTextSize(xml->attributes().value("textSize").toInt());
					object.setString(xml->attributes().value("string").toString());
					layoutModel->addItem(object);
				}
			}
		}
	}
}


void MainWindow::itemTracker_clicked(const QModelIndex& index) {
	if (index.data().isValid()) {
		auto id = index.data().value<ItemStatus>().itemId;
		auto item = itemDictionary[id];

		if (id.isEmpty()) {
			return;
		}

		auto level = itemLevels[id];

		if (!item.isProgressive() && !item.isStacking()) {
			itemLevels[id] = itemLevels[id] ? 0 : 1;
		}

		if (item.isProgressive()) {
			itemLevels[id] = (level < item.levels()) ? level + 1 : 0;
		}

		if (item.isStacking() && level < item.maxStacks()) {
			itemLevels[id] = level + 1;
		}

		// If the level changed, emit this change!
		auto newLevel = itemLevels[id];
		if (level != newLevel) {
			emit itemUpgradeLevelChanged(item, newLevel);
		}
	}
}

void MainWindow::closeEvent(QCloseEvent* event) {
	QWidget::closeEvent(event);
}

void MainWindow::parseStrings(QXmlStreamReader* xml) {
	while (!xml->atEnd() && xml->readNext()) {
		if (xml->name() == "StringList") {
			QStringList stringList;
			QString stringListId = xml->attributes().value("id").toString();

			while (!xml->atEnd() && xml->readNext()) {
				if (xml->name() == "String" && !xml->isEndElement()) {
					stringList.append(xml->readElementText());
				}

				if (xml->name() == "StringList" && xml->isEndElement()) {
					break;
				}
			}

			if (!stringListId.isEmpty()) {
				strings.insert(stringListId, stringList);
			}
		}

		if (xml->name() == "Strings" && xml->isEndElement()) {
			return;
		}
	}
}
