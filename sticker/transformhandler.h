#ifndef TRANSFORMHANDLER_H
#define TRANSFORMHANDLER_H

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QPointF>

#include "sticker.h"
#include "anchor.h"

class Anchor;
class Sticker;

class TransformHandler : public QGraphicsRectItem
{
public:
    TransformHandler(Sticker* parent);
    virtual ~TransformHandler();
    void init();
    void dragScale(QPointF scenePos);

private:
    Anchor* anchor;
    constexpr static const qreal minScale = 0.4;

};

#endif // TRANSFORMHANDLER_H
