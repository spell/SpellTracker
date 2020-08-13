//
// Created by Jesse on 8/11/2020.
//

#ifndef SPELLTRACKER_ITEMLAYOUTMODEL_H
#define SPELLTRACKER_ITEMLAYOUTMODEL_H

#include "Item.h"

#include <QAbstractTableModel>

struct ItemStatus {
	QString itemId;
	Item item;
	bool active{false};
};

class ItemLayoutModel : public QAbstractTableModel {
Q_OBJECT;



protected:
	QStringList itemLayout;
	QHash<QString, Item>* items;
	QHash<QString, int>* itemLevels;

public:
	explicit ItemLayoutModel(QHash<QString, Item>* itemDictionary, QHash<QString, int>* levels,
	                         QObject* parent = nullptr);

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

	void addItem(QString qString);

	void clear();

public slots:

	void upgradeLevelChanged(const Item& item, int newLevel);
};

Q_DECLARE_METATYPE(ItemStatus);


#endif //SPELLTRACKER_ITEMLAYOUTMODEL_H
