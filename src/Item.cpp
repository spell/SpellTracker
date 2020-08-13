//
// Created by Jesse on 8/4/2020.
//

#include "Item.h"

Item::Item(QStringView id, QStringView name, QStringView category, int icon)
		: id(id.toString()), name(name.toString()), category(category.toString()), icon(icon) {
	// do nothing
}

void Item::setUpgrades(const QStringList& upgradeIds) {
	progressiveUpgrades = upgradeIds;
}

void Item::setMaxCount(int count) {
	maxCount = (count >= 0) ? count : 0;
}
