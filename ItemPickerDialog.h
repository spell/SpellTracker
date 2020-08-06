//
// Created by Jesse on 8/6/2020.
//

#ifndef SPELLTRACKER_ITEMPICKERDIALOG_H
#define SPELLTRACKER_ITEMPICKERDIALOG_H

#include <QDialog>

class ItemPickerDialog: public QDialog {
	Q_OBJECT

public:
	ItemPickerDialog(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};


#endif //SPELLTRACKER_ITEMPICKERDIALOG_H
