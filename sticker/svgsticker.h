#ifndef SVGSTICKER_H
#define SVGSTICKER_H

#include "sticker.h"
#include <QSvgRenderer>
#include <QGraphicsSvgItem>

class SvgSticker : public Sticker
{
public:
    SvgSticker(const QString& filename);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override;

private:
    QGraphicsSvgItem svgItem;
};

#endif // SVGSTICKER_H
