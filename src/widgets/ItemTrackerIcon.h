//
// Created by jesse on 8/14/20.
//

#ifndef SPELLTRACKER_ITEMTRACKERICON_H
#define SPELLTRACKER_ITEMTRACKERICON_H

#include <QWidget>
#include <QString>
#include <QPixmap>

enum class TextPosition {
	Center,
	TopLeft,
	Top,
	TopRight,
	Right,
	BottomRight,
	Bottom,
	BottomLeft,
	Left,
};

class ItemTrackerIcon : public QWidget {
Q_OBJECT;

private:
	QPixmap icon;
	QString text;
	TextPosition textPosition{TextPosition::Bottom};
	int textSize{10};

protected:
	void paintEvent(QPaintEvent* event) override;

	void drawTextAtPosition(QPainter* painter);

public:
	explicit ItemTrackerIcon(QWidget* parent = nullptr);

	void setIcon(const QPixmap& pixmap);

	void setText(const QString& text);

	void setTextPosition(TextPosition position);

	void setTextSize(int size);
};


#endif //SPELLTRACKER_ITEMTRACKERICON_H
