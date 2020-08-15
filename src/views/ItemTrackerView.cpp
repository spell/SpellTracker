//
// Created by Jesse on 8/11/2020.
//

#include "ItemTrackerView.h"
#include "models/ItemLayoutModel.h"

#include <QLabel>
#include <QMouseEvent>
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

		ItemTrackerIcon* icon = nullptr;
		auto layoutItem = gridLayout->itemAtPosition(topLeft.row(), topLeft.column());

		if (layoutItem != nullptr) {
			icon = reinterpret_cast<ItemTrackerIcon*>(layoutItem->widget());
		} else {
			icon = new ItemTrackerIcon(this);
		}

		if (icon != nullptr) {
			if (!status.item.getId().isEmpty()) {
				icon->setIcon(icons.get(status.item.getIcon(), !status.active()));
				icon->setToolTip(status.item.getName());
				icon->setTextSize(status.layout.getTextSize());

				if (status.text.isEmpty()) {
					if (status.item.isStacking() && status.level > 0)
						icon->setText(QString::number(status.level));
					if (status.layout.hasText()) {
						icon->setText(status.layout.getText());
					}

					if (status.item.isStacking() && status.level == 0) {
						icon->setText(QString());
					}
				} else {
					icon->setText(status.text);
				}
			}

			if (layoutItem == nullptr) {
				gridLayout->addWidget(icon, topLeft.row(), topLeft.column(), Qt::AlignHCenter | Qt::AlignVCenter);
				icon->setAttribute(Qt::WA_TransparentForMouseEvents, true);
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

void ItemTrackerView::mouseReleaseEvent(QMouseEvent* event) {
	QAbstractItemView::mouseReleaseEvent(event);
	auto index = indexAt(event->pos());

	if (event->button() == Qt::MouseButton::LeftButton) {
		emit itemPrimaryClicked(index);
	} else if (event->button() == Qt::MouseButton::RightButton) {
		emit itemSecondaryClicked(index);
	}
}

