//
// Created by Jesse on 8/11/2020.
//

#ifndef SPELLTRACKER_ICONSET_H
#define SPELLTRACKER_ICONSET_H

#include <QIODevice>
#include <QPixmap>

class IconSetData : public QSharedData {
public:
	QHash<int, QPixmap> icons;
	QHash<int, QPixmap> grayscaleIcons;
	int iconSize{42};
};

class IconSet {
public:
	explicit IconSet() : d(new IconSetData()) {}
	explicit IconSet(const QString& filename);

	IconSet(const IconSet& other) = default;

	[[nodiscard]] QPixmap get(int iconIndex, bool grayscale = false) const;

	[[nodiscard]] int iconSize() const {
		return d->iconSize;
	}

private:
	QSharedDataPointer<IconSetData> d;

	[[nodiscard]] const QHash<int, QPixmap>& icons() const {
		return d->icons;
	}

	[[nodiscard]] const QHash<int, QPixmap>& grayscaleIcons() const {
		return d->grayscaleIcons;
	}

	static QImage convertImageToGrayscale(QImage image);
};


#endif //SPELLTRACKER_ICONSET_H
