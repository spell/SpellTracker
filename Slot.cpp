//
// Created by Jesse on 8/4/2020.
//

#include <QMouseEvent>

#include "Slot.h"

Slot::Slot(QWidget* parent) {
	setScaledContents(true);
	setFixedWidth(24);
	setFixedHeight(24);
	setFrameStyle(QFrame::Shape::StyledPanel);
}

void Slot::mousePressEvent(QMouseEvent* ev) {
	QLabel::mousePressEvent(ev);

	if (ev->button() == Qt::LeftButton) {
		emit onLeftClick(this);
	}

	if (ev->button() == Qt::RightButton) {
		emit onRightClick(this);
	}
}

void Slot::setItem(const Item& item) {
	if (item.getId().isEmpty()) {
		setPixmap(QPixmap());
	}

	auto& upgrade = item.getUpgradeLevel(0);
	setPixmap(upgrade.icon.value());
}
