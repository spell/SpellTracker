//
// Created by Jesse on 8/11/2020.
//

#ifndef SPELLTRACKER_ITEMTRACKERVIEW_H
#define SPELLTRACKER_ITEMTRACKERVIEW_H

#include "IconSet.h"

#include <QAbstractItemView>
#include <QGridLayout>

class ItemTrackerView : public QAbstractItemView {
Q_OBJECT;

signals:
	void itemPrimaryClicked(const QModelIndex& index);

	void itemSecondaryClicked(const QModelIndex& index);

public:
	explicit ItemTrackerView(QWidget* parent = nullptr);

	[[nodiscard]] QRect visualRect(const QModelIndex& index) const override;

	void scrollTo(const QModelIndex& index, ScrollHint hint) override;

	[[nodiscard]] QModelIndex indexAt(const QPoint& point) const override;

	void reset() override;

	void setIconSet(IconSet iconSet);

protected slots:
	void mouseReleaseEvent(QMouseEvent* event) override;

protected:
	void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles) override;

	QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;

	[[nodiscard]] int horizontalOffset() const override;

	[[nodiscard]] int verticalOffset() const override;

	[[nodiscard]] bool isIndexHidden(const QModelIndex& index) const override;

	void setSelection(const QRect& rect, QItemSelectionModel::SelectionFlags command) override;

	[[nodiscard]] QRegion visualRegionForSelection(const QItemSelection& selection) const override;

	void adjustSizeToContents();

private:
	QGridLayout* gridLayout;
	IconSet icons;
};


#endif //SPELLTRACKER_ITEMTRACKERVIEW_H
