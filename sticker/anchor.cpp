#include "anchor.h"

Anchor::Anchor(TransformHandler* parent) :
    QGraphicsRectItem(-RADIUS, -RADIUS, RADIUS*2, RADIUS*2, parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
//    setFlag(QGraphicsItem::ItemIgnoresTransformations);
}

Anchor::~Anchor() {}

void Anchor::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    TransformHandler* parent = dynamic_cast<TransformHandler*>(parentItem());
    parent->dragScale(mapToScene(event->pos()));
    event->accept();
}

#include <QDebug>
void Anchor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}
