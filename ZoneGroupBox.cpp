//
// Created by Jesse on 8/4/2020.
//

#include "ZoneGroupBox.h"

#include <QVBoxLayout>

ZoneGroupBox::ZoneGroupBox(const QString& zoneName, QWidget* parent) : QGroupBox(zoneName, parent) {
	setLayout(new QVBoxLayout(this));
}

SubzoneGroupBox* ZoneGroupBox::addSubzone(const QString& name) {
	auto* subzoneGroup = new SubzoneGroupBox(name, this);
	layout()->addWidget(subzoneGroup);
	return subzoneGroup;
}
