//
// Created by jesse on 8/14/20.
//

#ifndef SPELLTRACKER_ITEMTRACKERICON_H
#define SPELLTRACKER_ITEMTRACKERICON_H


#include <QGraphicsDropShadowEffect>
#include <QGridLayout>
#include <QLabel>
#include <QWidget>

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
    QGraphicsDropShadowEffect* shadowEffect;
    QGridLayout* layout;
    QLabel* icon;
    QLabel* text;

public:
    explicit ItemTrackerIcon(QWidget* parent = nullptr);

    void setIcon(const QPixmap& pixmap);
    void setText(const QString& text);
    void setTextPosition(TextPosition position);
};


#endif //SPELLTRACKER_ITEMTRACKERICON_H
