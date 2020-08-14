//
// Created by jesse on 8/14/20.
//

#include "ItemLayoutObject.h"

#include <utility>

ItemLayoutObject::ItemLayoutObject(QString itemId) : itemId(std::move(itemId)) {
    // do nothing, for now
}

void ItemLayoutObject::setString(const QString& id) {
	if (!id.isEmpty()) {
		stringId = id;
	}
}

void ItemLayoutObject::setTextSize(int size) {
	textSize = size;
}

void ItemLayoutObject::setText(const QString& t) {
	text = t;
}

void ItemLayoutObject::setTextPosition(TextPosition position) {
	textPosition = position;
}

void ItemLayoutObject::setItemId(const QString& id) {
	itemId = id;
}
