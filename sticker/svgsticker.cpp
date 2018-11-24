#include "svgsticker.h"

SvgSticker::SvgSticker(const QString& filename) :
    Sticker(),
    svgItem(filename)
{
    transformHandler->init();
    setTransformOriginPoint(boundingRect().bottomRight());
    setScale(5);
    QTransform matrix;
    int x = (boundingRect().width()-8) * 5 / 2;
    int y = (boundingRect().height()-8) * 5 / 2;
    matrix.translate(x,y);
    setTransform(matrix);
}

#include <QDebug>

void SvgSticker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    svgItem.paint(painter, option, widget);
}

QRectF SvgSticker::boundingRect() const
{
    return svgItem.boundingRect();
}

