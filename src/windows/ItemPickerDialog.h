//
// Created by Jesse on 8/6/2020.
//

#ifndef SPELLTRACKER_ITEMPICKERDIALOG_H
#define SPELLTRACKER_ITEMPICKERDIALOG_H

#include "Item.h"

#include <QDialog>

class ItemPickerDialog : public QDialog {
Q_OBJECT

public:
	explicit ItemPickerDialog(const QHash<QString, Item>& items, QWidget* parent = nullptr,
	                          Qt::WindowFlags f = Qt::Popup);
};


#endif //SPELLTRACKER_ITEMPICKERDIALOG_H
