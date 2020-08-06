//
// Created by Jesse on 8/4/2020.
//

#ifndef SPELLTRACKER_SUBZONEGROUPBOX_H
#define SPELLTRACKER_SUBZONEGROUPBOX_H

#include "Check.h"

#include <QGroupBox>

class SubzoneGroupBox : public QGroupBox {
	Q_OBJECT

public:
	explicit SubzoneGroupBox(const QString& subzoneName, QWidget* parent = nullptr);
	Check* addCheck(const QString& id, const QString& name);
};


#endif //SPELLTRACKER_SUBZONEGROUPBOX_H
