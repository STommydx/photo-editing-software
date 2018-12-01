#include "anchor.h"

Anchor::Anchor(QGraphicsItem *parent, int type) :
    QGraphicsRectItem(-RADIUS, -RADIUS, RADIUS*2, RADIUS*2, parent),
    type(type)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
    setVisible(false);
}

Anchor::~Anchor() {}

void Anchor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    parentItem()->setVisible(true);
    event->accept();
}

void Anchor::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    parentItem()->setVisible(true);
    switch(type)
    {
    case RESIZE:
        dragScale(event->scenePos()); break;
    case ROTATE:
        dragRotate(event->scenePos()); break;
    }
    event->accept();
}

void Anchor::dragScale(QPointF scenePos)
{
    QRectF rect0, rect1;
    rect0 = rect1 = parentItem()->sceneBoundingRect();
    rect1.setTopLeft(scenePos);
    QSizeF size(rect0.width(), rect0.height());
    size.scale(rect1.width(), rect1.height(), Qt::KeepAspectRatioByExpanding);
    qreal scale1 = parentItem()->scale() * (size.width() / rect0.width());
    if(scale1 > MIN_SCALE)
        parentItem()->setScale(scale1);
}

void Anchor::dragRotate(QPointF pos) { /* TODO */ }
