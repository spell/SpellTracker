//
// Created by Jesse on 8/4/2020.
//

#include <iostream>

#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>

#include "Check.h"

Check::Check(const QString& id, const QString& name, QWidget* parent) : QWidget(parent), id(id) {
	setLayout(new QHBoxLayout(this));
	layout()->setContentsMargins(1, 1, 1, 1);

	auto* checkBox = new QCheckBox(name, this);
	connect(checkBox, &QCheckBox::stateChanged, this, &Check::onStateChanged);
	layout()->addWidget(checkBox);
}

void Check::onStateChanged(int state) {
	emit checkStatusChanged(id, state == Qt::CheckState::Checked);
}

Slot* Check::addSlot(const QString& category, const QString& itemId, const QPixmap& pixmap) {
	auto* slot = new Slot(this);
	layout()->addWidget(slot);
	return slot;
}
