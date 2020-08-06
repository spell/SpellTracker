//
// Created by Jesse on 8/4/2020.
//

#include "SubzoneGroupBox.h"

#include <QVBoxLayout>

SubzoneGroupBox::SubzoneGroupBox(const QString& subzoneName, QWidget* parent) : QGroupBox(subzoneName, parent) {
	setFlat(true);
	setLayout(new QVBoxLayout(this));

}

Check* SubzoneGroupBox::addCheck(const QString& id, const QString& name) {
	auto* check = new Check(id, name, this);
	layout()->addWidget(check);
	return check;
}
