#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Item.h"
#include "IconSet.h"
#include "models/ItemLayoutModel.h"
#include "views/ItemTrackerView.h"
#include "windows/StreamerPopoutWindow.h"
#include "windows/SettingsDialog.h"

#include <QMainWindow>
#include <QGridLayout>
#include <QXmlStreamReader>
#include <QSettings>

#include <optional>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);

	~MainWindow() override;

public slots:

	void loadDataFile(const QString& path);

	bool loadIconSet(const QString& filename);

	void reloadSettings();

signals:

	void itemUpgradeLevelChanged(const Item& item, int level);

	void iconThemeChanged(const QPixmap& icons, const QPixmap& grayscaleIcons);

protected:
	void parseItems(QXmlStreamReader* xml);

	void parseItem(QXmlStreamReader* xml, QStringView category);

	void parseLayouts(QXmlStreamReader* xml);

	void parseLayout(QXmlStreamReader* xml, QWidget* target);

	void clearTracker();

protected slots:
	void itemTracker_clicked(const QModelIndex& index);

	void closeEvent(QCloseEvent* event) override;

private:
	Ui::MainWindow* ui;
	QSettings settings;
	SettingsDialog* settingsDialog;
	ItemLayoutModel* layoutModel;
	ItemTrackerView* itemTracker;
	StreamerPopoutWindow* popoutWindow;
	QHash<QString, Item> itemDictionary;
	QHash<QString, int> itemLevels;
	QHash<QString, QStringList> strings;
	IconSet iconSet;

	void parseStrings(QXmlStreamReader* xml);
};

#endif // MAINWINDOW_H
