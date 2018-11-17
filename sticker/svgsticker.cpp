#include "svgsticker.h"

SvgSticker::SvgSticker(const QString& filename) :
    Sticker(),
    svgItem(filename)
{
    transformHandler->init();
}

void SvgSticker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    svgItem.paint(painter, option, widget);
}

QRectF SvgSticker::boundingRect() const
{
    return svgItem.boundingRect();
}

