//
// Created by Jesse on 8/11/2020.
//

#include "ItemTrackerView.h"
#include "models/ItemLayoutModel.h"

#include <QLabel>
#include <iostream>
#include <Item.h>

ItemTrackerView::ItemTrackerView(QWidget* parent)
		: QAbstractItemView(parent),
		  gridLayout(new QGridLayout(this)) {
	setLayout(gridLayout);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

void
ItemTrackerView::dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles) {
	QAbstractItemView::dataChanged(topLeft, bottomRight, roles);
	adjustSizeToContents();

	if (!roles.contains(Qt::DisplayRole)) {
		return;
	}

	if (topLeft == bottomRight) {
		auto status = model()->data(topLeft, Qt::DisplayRole).value<ItemStatus>();
		QLabel* label = nullptr;
		auto layoutItem = gridLayout->itemAtPosition(topLeft.row(), topLeft.column());

		if (layoutItem != nullptr) {
			label = reinterpret_cast<QLabel*>(layoutItem->widget());
		} else {
			label = new QLabel(status.item.getId(), this);
		}

		if (label != nullptr) {
			if (!status.item.getId().isEmpty()) {
				label->setPixmap(icons.get(status.item.getIcon(), !status.active));
				label->setToolTip(status.item.getName());
			}

			if (layoutItem == nullptr) {
				gridLayout->addWidget(label, topLeft.row(), topLeft.column(), Qt::AlignHCenter | Qt::AlignVCenter);
				label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
			}
		}
	}
}

QRect ItemTrackerView::visualRect(const QModelIndex& index) const {
	return QRect();
}

void ItemTrackerView::scrollTo(const QModelIndex& index, QAbstractItemView::ScrollHint hint) {

}

QModelIndex ItemTrackerView::indexAt(const QPoint& point) const {
	if (model() != nullptr && model()->rowCount() > 0 && model()->columnCount() > 0) {
		return model()->index(point.y() / (height() / model()->rowCount()),
		                      point.x() / (width() / model()->columnCount()));
	}
	return QModelIndex();
}

QModelIndex ItemTrackerView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers) {
	return QModelIndex();
}

int ItemTrackerView::horizontalOffset() const {
	return 0;
}

int ItemTrackerView::verticalOffset() const {
	return 0;
}

bool ItemTrackerView::isIndexHidden(const QModelIndex& index) const {
	return false;
}

void ItemTrackerView::setSelection(const QRect& rect, QItemSelectionModel::SelectionFlags command) {

}

QRegion ItemTrackerView::visualRegionForSelection(const QItemSelection& selection) const {
	return QRegion();
}

void ItemTrackerView::reset() {
	QAbstractItemView::reset();
	qDeleteAll(findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
}

void ItemTrackerView::setIconSet(IconSet iconSet) {
	icons = iconSet;
}

void ItemTrackerView::adjustSizeToContents() {
	auto computedSize = icons.iconSize() + gridLayout->margin() + gridLayout->spacing();
	setMinimumSize(computedSize * model()->columnCount(),
	               computedSize * model()->rowCount());
}