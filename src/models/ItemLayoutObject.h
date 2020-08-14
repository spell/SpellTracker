//
// Created by jesse on 8/14/20.
//

#ifndef SPELLTRACKER_ITEMLAYOUTOBJECT_H
#define SPELLTRACKER_ITEMLAYOUTOBJECT_H

#include <QString>
#include "widgets/ItemTrackerIcon.h"

class ItemLayoutObject {
    QString itemId;
    QString text;
    TextPosition textPosition = {TextPosition::Bottom};


public:
    explicit ItemLayoutObject(QString itemId = QString());

    void setText(const QString& t) {
        text = t;
    }

    void setTextPosition(TextPosition position) {
        textPosition = position;
    }

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
};

#endif //SPELLTRACKER_ITEMLAYOUTOBJECT_H
