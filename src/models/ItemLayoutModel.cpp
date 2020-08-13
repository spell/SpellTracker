//
// Created by Jesse on 8/11/2020.
//

#include "ItemLayoutModel.h"

ItemLayoutModel::ItemLayoutModel(QHash<QString, Item>* itemDictionary, QHash<QString, int>* levels, QObject* parent)
		: QAbstractTableModel(parent),
		  items(itemDictionary),
		  itemLevels(levels) {
}

int ItemLayoutModel::rowCount(const QModelIndex& parent) const {
	return itemLayout.count() / 6 + ((itemLayout.count() % 6) ? 1 : 0);
}

int ItemLayoutModel::columnCount(const QModelIndex& parent) const {
	return 6;
}

ItemStatus ItemLayoutModel::getItemStatusForIndex(const QModelIndex& index) const {
	auto position = index.row() * 6 + index.column();
	auto itemId = itemLayout.at(position);
	auto level = itemLevels->value(itemId);

	ItemStatus status;
	status.itemId = itemId;
	status.item = items->value(itemId);
	status.active = level != 0;

	if (status.item.isProgressive()) {
		status.item = items->value(status.item.getUpgradeItemId(level));
	}

	return status;
}

QVariant ItemLayoutModel::data(const QModelIndex& index, int role) const {
	if (!index.isValid() || items == nullptr) {
		return QVariant();
	}

	if (index.row() * 6 + index.column() >= itemLayout.count()) {
		// Out of range!
		return QVariant();
	}

	auto status = getItemStatusForIndex(index);

	switch (role) {
		case Qt::DisplayRole: {
			return QVariant::fromValue(status);
		}

		case Qt::ToolTipRole: {
			return status.item.getName();
		}

		default: {
			return QVariant();
		}
	}
}

QVariant ItemLayoutModel::headerData(int section, Qt::Orientation orientation, int role) const {
	return QAbstractItemModel::headerData(section, orientation, role);
}

void ItemLayoutModel::addItem(QString itemId) {
	itemLayout.append(itemId);

	auto newItemIndex = index((itemLayout.count() - 1) / 6, (itemLayout.count() - 1) % 6);
	emit dataChanged(newItemIndex, newItemIndex, QVector<int>{Qt::DisplayRole});
}

void ItemLayoutModel::clear() {
	emit beginResetModel();
	itemLayout.clear();
	emit endResetModel();
}

void ItemLayoutModel::upgradeLevelChanged(const Item& item, int newLevel) {
	auto position = itemLayout.indexOf(item.getId());
	auto itemIndex = index(position / 6, position % 6);
	emit dataChanged(itemIndex, itemIndex, QVector<int>{Qt::DisplayRole});
}
