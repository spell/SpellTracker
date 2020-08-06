//
// Created by Jesse on 8/4/2020.
//

#ifndef SPELLTRACKER_ZONEGROUPBOX_H
#define SPELLTRACKER_ZONEGROUPBOX_H

#include <QGroupBox>
#include "SubzoneGroupBox.h"

class ZoneGroupBox : public QGroupBox {
Q_OBJECT

public:
	explicit ZoneGroupBox(const QString& zoneName, QWidget* parent = nullptr);
	SubzoneGroupBox* addSubzone(const QString& name);
};

#endif //SPELLTRACKER_ZONEGROUPBOX_H
