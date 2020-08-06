#include "MainWindow.h"
#include "ZoneGroupBox.h"
#include "./ui_MainWindow.h"
#include "ItemPickerDialog.h"

#include <iostream>

#include <QDir>
#include <QXmlStreamReader>

MainWindow::MainWindow(QWidget* parent)
		: QMainWindow(parent),
		  ui(new Ui::MainWindow),
		  itemTracker(new ItemTracker(this)) {
	ui->setupUi(this);
	ui->itemTrackerLayout->insertWidget(ui->itemTrackerLayout->count() - 1, itemTracker);

	connect(this, &MainWindow::itemUpgradeLevelChanged, itemTracker, &ItemTracker::onUpgradeLevelChanged);

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
	std::cout << "Opening file: " << path.toStdString() << std::endl;
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

	// Load the icon set used by the file
	// TODO: Check settings to see if the user selected an icon set for this data file and
	//       load that one instead.
	if (xml.attributes().hasAttribute("icons")) {
		auto iconSetFilename = xml.attributes().value("icons").toString();

		if (loadIconSet(iconSetFilename)) {
			iconSize = xml.attributes().value("iconSize").toInt();
			if (iconSize == 0) {
				statusBar()->showMessage(
						QString{"Icon set '%1' has invalid icon size: %2"}.arg(iconSetFilename).arg(iconSize));
				return;
			}

			auto iconsPerRow = iconSet->width() / iconSize;
			auto totalIcons = iconSet->height() / iconSize * iconsPerRow;
			std::cout << QString{"Loaded %1 icons from %2"}.arg(totalIcons).arg(iconSetFilename).toStdString() << "\n";
		} else {
			statusBar()->showMessage(QString{"Could not load icon set: %1"}.arg(iconSetFilename));
		}
	}

	// Read the file in earnest now.
	while (!xml.atEnd()) {
		xml.readNext();

		if (!xml.isEndElement()) {
			std::cout << xml.name().toString().toStdString() << std::endl;

			if (xml.name() == "Items") {
				parseItems(&xml);
			}

			if (xml.name() == "Zone") {
				parseZoneData(&xml);
			}
		}
	}

	if (xml.hasError()) {
		statusBar()->showMessage(QString{"Error while reading data for '%1': %2"}
				                         .arg(name)
				                         .arg(xml.errorString()));
		return;
	}

	emit itemUpgradeLevelChanged(itemDictionary["hookshot"], 0);
}

void MainWindow::clearTracker() {
	qDeleteAll(ui->logicTrackerScrollContent->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
	itemDictionary.clear();
	iconSet.reset();
}

bool MainWindow::loadIconSet(const QString& filename) {
	QDir iconsDirectory("icons");
	QString iconPath = iconsDirectory.filePath(filename);

	if (!QFile::exists(iconPath)) {
		return false;
	}

	iconSet = QPixmap(iconPath);
	return true;
}

void MainWindow::parseItems(QXmlStreamReader* xml) {
	QString category;
	itemTracker->clear();

	while (!xml->atEnd()) {
		xml->readNext();

		if (xml->name() == "Items" && xml->isEndElement()) {
			break;
		}

		if (xml->name() == "Category") {
			category = xml->attributes().value("id").toString();
			continue;
		}

		if (xml->name() == "Item") {
			parseItem(xml, category);
		}
	}
}

void MainWindow::parseItem(QXmlStreamReader* xml, QStringView category) {
	auto id = xml->attributes().value("id").toString();
	Item item(id, category);

	while (!xml->atEnd()) {
		xml->readNext();

		if (xml->name() == "Item" && xml->isEndElement()) {
			break;
		}

		if (xml->name() == "Upgrade" && !xml->isEndElement()) {
			auto name = xml->attributes().value("name").toString();
			auto iconIndex = xml->attributes().value("icon").toInt();

			if (iconSet) {
				auto iconsPerRow = iconSet->width() / iconSize;
				auto row = iconIndex / iconsPerRow;
				auto col = iconIndex % iconsPerRow;

				auto icon = iconSet->copy(col * iconSize, row * iconSize, iconSize, iconSize);
				item.addUpgrade(name, icon);
			} else {
				item.addUpgrade(name, QPixmap());
			}
		}
	}

	// Add the item into the dictionary and also set its upgrade level to zero.
	itemDictionary.insert(id, item);
	itemUpgradeLevels.insert(id, 0);
	itemTracker->addItem(item);
}

void MainWindow::parseZoneData(QXmlStreamReader* xml) {
	if (xml->name() != "Zone" && !xml->isStartElement()) {
		statusBar()->showMessage(QString{"parseZoneData: expected 'Zone' but got: %1"}.arg(xml->name()));
		return;
	}

	auto zoneName = xml->attributes().value("name").toString();
	auto* zoneGroupBox = new ZoneGroupBox(zoneName, ui->logicTrackerScrollContent);

	while (xml->readNext() && !xml->isEndElement() && xml->name() != "Zone") {
		if (xml->name() == "Subzone") {
			auto* subzone = zoneGroupBox->addSubzone(xml->attributes().value("name").toString());

			while (xml->readNext() && xml->name() != "Subzone") {
				if (xml->name() == "Check" && !xml->isEndElement()) {
					auto* check = subzone->addCheck(
							xml->attributes().value("id").toString(),
							xml->attributes().value("name").toString()
					);

					connect(check, &Check::checkStatusChanged, this, &MainWindow::onCheckStatusChanged);

					while (xml->readNext() && xml->name() != "Check") {
						if (xml->name() == "Slot" && !xml->isEndElement()) {
							auto category = xml->attributes().value("category").toString();
							auto* slot = check->addSlot(category);

							connect(slot, &Slot::onLeftClick, this, [=]() {
								ItemPickerDialog dialog(this, Qt::Popup);
								dialog.exec();
							});
						}
					}
				}
			}
		}
	}

	// Finally add the box.
	ui->logicTrackerLayout->insertWidget(ui->logicTrackerLayout->count() - 1, zoneGroupBox);
	zoneGroupBox->show();
}

void MainWindow::onCheckStatusChanged(const QString& id, bool completed) {
	std::cout
			<< "Check '" << id.toStdString() << "' has been "
			<< ((completed) ? "completed" : "un-completed")
			<< std::endl;
}


void MainWindow::incrementItemUpgradeLevel(const QString& id) {
	if (itemUpgradeLevels.contains(id)) {
		itemUpgradeLevels[id]++;
		emit itemUpgradeLevelChanged(itemDictionary[id], ++itemUpgradeLevels[id]);
	}
}

void MainWindow::decrementItemUpgradeLevel(const QString& id) {
	if (itemUpgradeLevels.contains(id)) {
		if (itemUpgradeLevels[id] > 0) {
			emit itemUpgradeLevelChanged(itemDictionary[id], --itemUpgradeLevels[id]);
		}
	}
}
