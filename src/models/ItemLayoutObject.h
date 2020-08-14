//
// Created by jesse on 8/14/20.
//

#ifndef SPELLTRACKER_ITEMLAYOUTOBJECT_H
#define SPELLTRACKER_ITEMLAYOUTOBJECT_H

#include <QString>
#include "widgets/ItemTrackerIcon.h"

class ItemLayoutObject {
	QString itemId;
	QString stringId;
	QString text;
	int textSize; // in points
	TextPosition textPosition = {TextPosition::Bottom};

public:
	explicit ItemLayoutObject(QString itemId = QString());

	void setItemId(const QString& id);

	void setText(const QString& t);

	void setTextSize(int size);

	void setTextPosition(TextPosition position);

	void setString(const QString& stringId);

	[[nodiscard]] bool isNull() const {
		return itemId.isEmpty();
	}

	[[nodiscard]] const QString& getItemId() const {
		return itemId;
	}

	[[nodiscard]] bool hasText() const {
		return !text.isEmpty();
	}

	[[nodiscard]] const QString& getText() const {
		return text;
	}

	[[nodiscard]] TextPosition getTextPosition() const {
		return textPosition;
	}

	[[nodiscard]] int getTextSize() const {
		return textSize;
	}

	[[nodiscard]] bool hasString() const {
		return !stringId.isEmpty();
	}

	[[nodiscard]] const QString& getString() const {
		return stringId;
	}
};

#endif //SPELLTRACKER_ITEMLAYOUTOBJECT_H
