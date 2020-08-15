//
// Created by Jesse on 8/11/2020.
//

#include "ItemLayoutModel.h"

ItemLayoutModel::ItemLayoutModel(QHash<QString, Item>* itemDictionary, QHash<QString, int>* levels,
                                 QHash<QString, QStringList>* itemStrings, QObject* parent)
		: QAbstractTableModel(parent),
		  items(itemDictionary),
		  itemLevels(levels),
		  itemStrings(itemStrings) {
	// do nothing for now!
}

int ItemLayoutModel::rowCount(const QModelIndex& parent) const {
	return itemLayout.count() / 6 + ((itemLayout.count() % 6) ? 1 : 0);
}

int ItemLayoutModel::columnCount(const QModelIndex& parent) const {
	return 6;
}

ItemStatus ItemLayoutModel::getItemStatusForIndex(const QModelIndex& index) const {
	auto position = index.row() * 6 + index.column();
	auto layout = itemLayout.at(position);
	auto level = itemLevels->value(layout.getItemId());

	ItemStatus status;
	status.layout = layout;
	status.itemId = layout.getItemId();
	status.item = items->value(layout.getItemId());
	status.level = level;

	if (layout.hasString() && itemTexts.contains(layout.getItemId())) {
		status.text = itemTexts[layout.getItemId()];
	}

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

void ItemLayoutModel::addItem(const QString& itemId) {
	addItem(ItemLayoutObject(itemId));
}

void ItemLayoutModel::addItem(const ItemLayoutObject& item) {
	itemLayout.append(item);
	auto newItemIndex = index((itemLayout.count() - 1) / 6, (itemLayout.count() - 1) % 6);
	emit dataChanged(newItemIndex, newItemIndex, QVector<int>{Qt::DisplayRole});
}

void ItemLayoutModel::clear() {
	emit beginResetModel();
	itemLayout.clear();
	itemTexts.clear();
	emit endResetModel();
}

void ItemLayoutModel::upgradeLevelChanged(const Item& item, int newLevel) {
	auto layoutObject = std::find_if(
			itemLayout.constBegin(),
			itemLayout.constEnd(),
			[item](const ItemLayoutObject& a) -> bool {
				return a.getItemId() == item.getId();
			}
	);

	auto position = std::distance(itemLayout.constBegin(), layoutObject);
	auto itemIndex = index(position / 6, position % 6);
	emit dataChanged(itemIndex, itemIndex, QVector<int>{Qt::DisplayRole});
}

void ItemLayoutModel::itemTextToggled(const QModelIndex& index) {
	auto status = index.data().value<ItemStatus>();
	auto itemId = status.itemId;

	auto layoutObject = std::find_if(
			itemLayout.constBegin(),
			itemLayout.constEnd(),
			[itemId](const ItemLayoutObject& a) -> bool {
				return a.getItemId() == itemId;
			}
	);

	if (status.item.isStacking()) {
		auto level = itemLevels->value(itemId);
		if (level > 0) {
			itemLevels->insert(itemId, level - 1);
		}
	} else if (layoutObject->hasString()) {
		auto list = itemStrings->value(layoutObject->getString());
		auto current = itemTexts[itemId];

		if (current == list.last()) {
			itemTexts[itemId] = QString();
		} else if (current.isEmpty()) {
			itemTexts[itemId] = list.first();
		} else {
			auto i = list.indexOf(current);
			itemTexts[itemId] = list.at(i + 1);
		}
	}

	emit dataChanged(index, index, QVector<int>{Qt::DisplayRole});
}
