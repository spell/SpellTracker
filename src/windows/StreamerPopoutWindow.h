//
// Created by Jesse on 8/14/2020.
//

#ifndef SPELLTRACKER_STREAMERPOPOUTWINDOW_H
#define SPELLTRACKER_STREAMERPOPOUTWINDOW_H

#include <QWidget>

#include "models/ItemLayoutModel.h"
#include "views/ItemTrackerView.h"
#include "IconSet.h"

class StreamerPopoutWindow : public QWidget {
Q_OBJECT;

private:
	ItemTrackerView* view;

public:
	StreamerPopoutWindow(ItemLayoutModel* model, const IconSet& icons, QWidget* parent = nullptr);

	void setIcons(const IconSet& icons);
};


#endif //SPELLTRACKER_STREAMERPOPOUTWINDOW_H
