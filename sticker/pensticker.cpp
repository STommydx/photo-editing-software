#include "pensticker.h"

PenSticker::PenSticker() :
    Sticker()
{
    transformHandler->init();
}

void PenSticker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    pathItem.paint(painter, option, widget);
}

QRectF PenSticker::boundingRect() const
{
    return pathItem.boundingRect();
}

Sticker::Type PenSticker::getType() const
{
    return Sticker::Pen;
}

QPainterPath PenSticker::path()
{
    return pathItem.path();
}

void PenSticker::setPath(QPainterPath& path)
{
    pathItem.setPath(path);
}

void PenSticker::setPen(const QPen& pen)
{
    pathItem.setPen(pen);
}

