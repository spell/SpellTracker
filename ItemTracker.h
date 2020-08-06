//
// Created by Jesse on 8/5/2020.
//

#ifndef SPELLTRACKER_ITEMTRACKER_H
#define SPELLTRACKER_ITEMTRACKER_H

#include "Item.h"

#include <QFrame>
#include <QGridLayout>
#include <QHash>

class ItemTracker : public QFrame {
	Q_OBJECT

protected:
	QGridLayout* gridLayout;
	int gridWidth;

public:
	explicit ItemTracker(QWidget* parent = nullptr, int width = 6);
	void addItem(const Item& item);
	void clear();

public slots:
	void onUpgradeLevelChanged(const Item& item, int level);
};


#endif //SPELLTRACKER_ITEMTRACKER_H
