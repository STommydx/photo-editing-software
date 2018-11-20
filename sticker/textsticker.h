#ifndef TEXTSTICKER_H
#define TEXTSTICKER_H

#include "sticker.h"

class TextSticker : public Sticker
{
public:
    TextSticker(const QString &text, const QFont &font = QFont("Times", 64), const QColor &color = Qt::black);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override;

private:
    QGraphicsTextItem textItem;
};

#endif // TEXTSTICKER_H
