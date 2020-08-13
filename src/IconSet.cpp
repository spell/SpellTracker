//
// Created by Jesse on 8/11/2020.
//

#include "IconSet.h"

IconSet::IconSet(const QString& filename)
		: d(new IconSetData) {
	QImage imageData(filename);
	QPixmap colorData = QPixmap::fromImage(imageData);
	QPixmap grayscaleData = QPixmap::fromImage(convertImageToGrayscale(imageData));

	d->iconSize = imageData.width() / 6;
	auto rows = imageData.height() / iconSize();

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < 6; x++) {
			auto xOffset = x * iconSize();
			auto yOffset = y * iconSize();
			auto index = y * 6 + x;
			d->icons.insert(index, colorData.copy(xOffset, yOffset, iconSize(), iconSize()));
			d->grayscaleIcons.insert(index, grayscaleData.copy(xOffset, yOffset, iconSize(), iconSize()));
		}
	}
}

QPixmap IconSet::get(int iconIndex, bool grayscale) const {
	if (grayscale) {
		return grayscaleIcons().value(iconIndex);
	} else {
		return icons().value(iconIndex);
	}
}

QImage IconSet::convertImageToGrayscale(QImage source) {
	QImage target = source.copy();

	for (int y = 0; y < target.height(); ++y) {
		QRgb* pixels = reinterpret_cast<QRgb*>(target.scanLine(y));

		for (int x = 0; x < target.width(); ++x) {
			QRgb* pixel = pixels + x;
			uint g = qGray(*pixel);
			*pixel = qRgba(g/1.5, g/1.5, g/1.5, qAlpha(*pixel));
		}
	}

	return target;
}
