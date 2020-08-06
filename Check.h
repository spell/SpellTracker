//
// Created by Jesse on 8/4/2020.
//

#ifndef SPELLTRACKER_CHECK_H
#define SPELLTRACKER_CHECK_H

#include "Slot.h"

#include <QWidget>

class Check : public QWidget {
Q_OBJECT

public:
	Check(const QString& id, const QString& name, QWidget* parent = nullptr);

	Slot* addSlot(const QString& category, const QString& itemId = "", const QPixmap& pixmap = QPixmap());

protected:
	QString id;

private slots:

	void onStateChanged(int state);

signals:

	void checkStatusChanged(const QString& id, bool completed);

	void itemStatusChanged(const QString& itemId, bool acquired);
};

#endif //SPELLTRACKER_CHECK_H
