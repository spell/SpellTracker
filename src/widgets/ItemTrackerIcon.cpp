//
// Created by jesse on 8/14/20.
//

#include "ItemTrackerIcon.h"

ItemTrackerIcon::ItemTrackerIcon(QWidget* parent)
        : QWidget(parent),
          layout(new QGridLayout(this)),
          icon(new QLabel(this)),
          text(new QLabel(this)),
          shadowEffect(new QGraphicsDropShadowEffect(this)) {
    shadowEffect->setBlurRadius(0);
    shadowEffect->setColor(QColor("#101010"));
    shadowEffect->setOffset(1,1);

    layout->addWidget(icon, 1, 1);
    text->setFont(QFont("arial", 10, QFont::Bold));
    text->setGraphicsEffect(shadowEffect);
    text->hide();
    setTextPosition(TextPosition::Bottom);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void ItemTrackerIcon::setIcon(const QPixmap& pixmap) {
    if (!pixmap.isNull()) {
        icon->setPixmap(pixmap);
        icon->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        icon->setMinimumSize(pixmap.size());
        setMinimumSize(pixmap.size());
        icon->show();
    } else {
        setMinimumSize(0,0);
        icon->clear();
        icon->hide();
    }
}

void ItemTrackerIcon::setText(const QString& t) {
    text->setText(t);
    text->setVisible(!t.isEmpty());
}

void ItemTrackerIcon::setTextPosition(TextPosition position) {
    switch (position) {
        case TextPosition::TopLeft:
            text->setAlignment(Qt::AlignLeft);
            layout->addWidget(text, 0, 0, Qt::AlignLeft | Qt::AlignTop);
            break;

        case TextPosition::Top:
            text->setAlignment(Qt::AlignCenter);
            layout->addWidget(text, 0, 1, Qt::AlignHCenter | Qt::AlignTop);
            break;

        case TextPosition::TopRight:
            text->setAlignment(Qt::AlignRight);
            layout->addWidget(text, 0, 2, Qt::AlignRight | Qt::AlignTop);
            break;

        case TextPosition::Right:
            text->setAlignment(Qt::AlignRight);
            layout->addWidget(text, 1, 2, Qt::AlignRight | Qt::AlignVCenter);
            break;

        case TextPosition::BottomRight:
            text->setAlignment(Qt::AlignRight);
            layout->addWidget(text, 2, 2, Qt::AlignRight | Qt::AlignBottom);
            break;

        case TextPosition::Bottom:
            text->setAlignment(Qt::AlignCenter);
            layout->addWidget(text, 2, 1, Qt::AlignHCenter | Qt::AlignBottom);
            break;

        case TextPosition::BottomLeft:
            text->setAlignment(Qt::AlignLeft);
            layout->addWidget(text, 2, 0, Qt::AlignLeft | Qt::AlignBottom);
            break;

        case TextPosition::Left:
            text->setAlignment(Qt::AlignLeft);
            layout->addWidget(text, 1, 0, Qt::AlignLeft | Qt::AlignVCenter);
            break;

        case TextPosition::Center:
        default:
            text->setAlignment(Qt::AlignCenter);
            layout->addWidget(text, 1, 1, Qt::AlignHCenter | Qt::AlignVCenter);
            break;
    }
}
