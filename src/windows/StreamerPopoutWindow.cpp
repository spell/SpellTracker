//
// Created by Jesse on 8/14/2020.
//

#include "StreamerPopoutWindow.h"

StreamerPopoutWindow::StreamerPopoutWindow(ItemLayoutModel* model, const IconSet& icons, QWidget* parent)
		: QWidget(parent),
		  view(new ItemTrackerView(this)) {
	setWindowTitle(tr("Streaming Popout"));
	setWindowFlags(Qt::Window);
	setLayout(new QGridLayout(this));
	layout()->addWidget(view);
	layout()->setSpacing(0);
	reinterpret_cast<QGridLayout*>(layout())->setMargin(0);

	view->setFrameStyle(QFrame::NoFrame);
	view->setModel(model);

	setStyleSheet("background-color: #2A3439");
	setStyleSheet("font-family: 'Impact'");
}

void StreamerPopoutWindow::setIcons(const IconSet& icons) {
	view->setIconSet(icons);
}
