#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Item.h"
#include "ItemTracker.h"

#include <QMainWindow>
#include <QGridLayout>
#include <QXmlStreamReader>

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

	/**
	 * Increases the upgrade level of an item by one.
	 * @param id The id of the item to upgrade.
	 */
	void incrementItemUpgradeLevel(const QString& id);

	/**
	 * Decreases the upgrade level of an item by one, down to to a maximum of zero.
	 * @param id The id of the item to upgrade.
	 */
	void decrementItemUpgradeLevel(const QString& id);

	void loadDataFile(const QString& path);

	bool loadIconSet(const QString& filename);

	void onCheckStatusChanged(const QString& id, bool completed);

signals:
	void itemUpgradeLevelChanged(const Item& item, int level);

protected:
	ItemTracker* itemTracker;

	QHash<QString, Item> itemDictionary;
	QHash<QString, int> itemUpgradeLevels;
	std::optional<QPixmap> iconSet;
	int iconSize;

private:
	Ui::MainWindow* ui;

	void parseZoneData(QXmlStreamReader* xml);

	void parseItems(QXmlStreamReader* xml);

	void parseItem(QXmlStreamReader* xml, QStringView category);

	void clearTracker();
};

#endif // MAINWINDOW_H
