//
// Created by jesse on 8/14/20.
//

#include <QPainter>
#include <QPainterPath>
#include "ItemTrackerIcon.h"

ItemTrackerIcon::ItemTrackerIcon(QWidget* parent) : QWidget(parent) {
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void ItemTrackerIcon::setIcon(const QPixmap& pixmap) {
	icon = pixmap;
	setMinimumSize(icon.size() * scale);
	resize(icon.size() * scale);
	update();
}

void ItemTrackerIcon::setText(const QString& t) {
	text = t;
	update();
}

void ItemTrackerIcon::setTextPosition(TextPosition position) {
	textPosition = position;
	update();
}

void ItemTrackerIcon::paintEvent(QPaintEvent* event) {
	QWidget::paintEvent(event);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

	if (!icon.isNull()) {
		painter.drawPixmap(QRect(0, 0, width(), height()), icon);
	}

	if (!text.isNull()) {
		drawTextAtPosition(&painter);
	}
}

void ItemTrackerIcon::setTextSize(int size) {
	textSize = size > 10 ? size : 10;
	update();
}

void ItemTrackerIcon::drawTextAtPosition(QPainter* painter) {
	QFont font("Impact", textSize * scale);
	painter->setFont(font);

	QPen pen;
	pen.setWidth(2);
	pen.setColor(Qt::black);
	painter->setPen(pen);

	QPainterPath path;
	path.addText(0, 0, font, text);
	// Position the text vertically and horizontally in the origin of the widget,
	// and then move it to the middle.
	path.translate(-path.boundingRect().width() / 2, (height() - (height() - textSize)) / 2);
	path.translate(height() / 2, width() / 2);

	auto halfWidth = width() / 2;
	auto halfTWidth = path.boundingRect().width() / 2 + pen.width();
	auto halfHeight = height() / 2;
	auto halfTHeight = path.boundingRect().height() / 2 + pen.width();

	// Now, finally, reposition the text where it wants to go.
	switch (textPosition) {
		case TextPosition::TopLeft:
			path.translate(-halfWidth + halfTWidth, -halfHeight + halfTHeight);
			break;

		case TextPosition::Top:
			path.translate(0, -halfHeight + halfTHeight);
			break;

		case TextPosition::TopRight:
			path.translate(halfWidth - halfTWidth, -halfHeight + halfTHeight);
			break;

		case TextPosition::Right:
			path.translate(halfWidth - halfTWidth, 0);
			break;

		case TextPosition::BottomRight:
			path.translate(halfWidth - halfTWidth, halfHeight - halfTHeight);
			break;

		case TextPosition::Bottom:
			path.translate(0, halfHeight - halfTHeight);
			break;

		case TextPosition::BottomLeft:
			path.translate(-halfWidth + halfTWidth, halfHeight - halfTHeight);
			break;

		case TextPosition::Left:
			path.translate(-halfWidth + halfTWidth, 0);
			break;

		case TextPosition::Center:
		default:
			break;
	}

	painter->drawPath(path);
	painter->fillPath(path, QBrush(QColor("#ffffff")));
}

void ItemTrackerIcon::setScale(qreal s) {
	scale = s;
	setMinimumSize(icon.size() * scale);
	resize(icon.size() * scale);
	update();
}
