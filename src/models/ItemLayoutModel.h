//
// Created by Jesse on 8/11/2020.
//

#ifndef SPELLTRACKER_ITEMLAYOUTMODEL_H
#define SPELLTRACKER_ITEMLAYOUTMODEL_H

#include "Item.h"
#include "models/ItemLayoutObject.h"

#include <QAbstractTableModel>

struct ItemStatus {
	ItemLayoutObject layout;
	QString itemId;
	QString text;
	Item item;
	int level;

	[[nodiscard]] bool active() const {
		return level > 0;
	}
};

class ItemLayoutModel : public QAbstractTableModel {
Q_OBJECT;

protected:
	QList<ItemLayoutObject> itemLayout;
	QHash<QString, Item>* items;
	QHash<QString, int>* itemLevels;
	QHash<QString, QStringList>* itemStrings; // TODO: We can do better than this.
	QHash<QString, QString> itemTexts;

public:
	explicit ItemLayoutModel(QHash<QString, Item>* itemDictionary, QHash<QString, int>* levels,
	                         QHash<QString, QStringList>* itemStrings, QObject* parent = nullptr);

	[[nodiscard]]
	ItemStatus getItemStatusForIndex(const QModelIndex& index) const;

	[[nodiscard]]
	QVariant data(const QModelIndex& index, int role) const override;

	[[nodiscard]]
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	[[nodiscard]]
	int rowCount(const QModelIndex& parent) const override;

	[[nodiscard]]
	int columnCount(const QModelIndex& parent) const override;

	void addItem(const QString& itemId);

	void addItem(const ItemLayoutObject& item);

	void clear();

public slots:

	void upgradeLevelChanged(const Item& item, int newLevel);

	void itemTextToggled(const QModelIndex& item);
};

Q_DECLARE_METATYPE(ItemStatus);


#endif //SPELLTRACKER_ITEMLAYOUTMODEL_H
