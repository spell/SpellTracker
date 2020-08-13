//
// Created by Jesse on 8/6/2020.
//

#include <QGridLayout>
#include <QLabel>

#include "ItemPickerDialog.h"

ItemPickerDialog::ItemPickerDialog(const QHash<QString, Item>& items, QWidget* parent, Qt::WindowFlags f)
		: QDialog(parent, f) {
	auto* grid = new QGridLayout(this);
	setLayout(grid);

	setStyleSheet("border: 1px solid black");
	int index = 0;

	// Create a quick grid of items
	for (const auto& v: items) {
		index++;
	}
}
