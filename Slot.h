//
// Created by Jesse on 8/4/2020.
//

#ifndef SPELLTRACKER_SLOT_H
#define SPELLTRACKER_SLOT_H

#include <QLabel>

#include "Item.h"

class Slot : public QLabel {
Q_OBJECT

private slots:

	void mousePressEvent(QMouseEvent* ev) override;

public:
	explicit Slot(QWidget* parent = nullptr);

public slots:
	void setItem(const Item& item);

signals:

	void onLeftClick(Slot* slot);

	void onRightClick(Slot* slot);
};


#endif //SPELLTRACKER_SLOT_H
