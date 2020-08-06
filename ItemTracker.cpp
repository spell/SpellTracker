//
// Created by Jesse on 8/5/2020.
//

#include "ItemTracker.h"

#include <QBitmap>
#include <QLabel>
#include <QVariant>
#include <QVBoxLayout>
#include <iostream>

ItemTracker::ItemTracker(QWidget* parent, int width)
		: QFrame(parent),
		  gridWidth(width),
		  gridLayout(new QGridLayout(this)) {
	setLayout(gridLayout);
}

void ItemTracker::addItem(const Item& item) {
	auto& baseUpgrade = item.getUpgradeLevel(0);

	// Create a new label with this panel as its parent.
	auto* label = new QLabel(this);
	label->setPixmap(baseUpgrade.icon.value());
	label->setToolTip(baseUpgrade.name);
	label->setScaledContents(true);
	label->show();

	label->setProperty("item-id", QVariant(item.getId()));

	// Add it to the layout at the right location.
	gridLayout->addWidget(label,
	                      gridLayout->count() / gridWidth,
	                      gridLayout->count() % gridWidth,
	                      Qt::AlignHCenter | Qt::AlignVCenter);
}

void ItemTracker::clear() {
	qDeleteAll(findChildren<QWidget *>("", Qt::FindDirectChildrenOnly));
}

void ItemTracker::onUpgradeLevelChanged(const Item& item, int level) {
	auto itemLabels = findChildren<QLabel*>("", Qt::FindDirectChildrenOnly);

	for (const auto& itemLabel: itemLabels) {
		auto itemId = itemLabel->property("item-id").toString();
		if (itemId == item.getId()) {
			auto& upgrade = item.getUpgradeLevel(level);

			if (level == 0) {
				itemLabel->setPixmap(upgrade.grayscaleIcon.value());
			} else {
				itemLabel->setPixmap(upgrade.icon.value());
			}
		}
	}
}
