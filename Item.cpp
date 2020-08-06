//
// Created by Jesse on 8/4/2020.
//

#include "Item.h"

Item::Item(const QStringView& id, const QStringView& category)
		: id(id.toString()), category(category.toString()) {
	// do nothing
}

void Item::addUpgrade(const QString& name, const QPixmap& icon) {
	upgrades.append(Upgrade(name, icon));
}

Item::Upgrade::Upgrade(const QString& name) : name(name) {
	// do nothing
}

Item::Upgrade::Upgrade(const QString& name, const QPixmap& icon)
		: name(name), icon(icon) {
	// Convert our pixmap to an image so we can draw to it efficiently.
	QImage image = icon.toImage();

	for (int row = 0; row < image.height(); row++) {
		QRgb* scan = reinterpret_cast<QRgb*>(image.scanLine(row));

		for (int i = 0; i < image.width(); i++) {
			QRgb pixel = *scan;
			uint gray = qGray(pixel);

			*scan = qRgba(gray, gray, gray, qAlpha(pixel));
			++scan;
		}
	}

	grayscaleIcon = QPixmap::fromImage(image);
}
