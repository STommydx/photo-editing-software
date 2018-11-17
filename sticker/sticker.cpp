#include "sticker.h"
#include <QDrag>

Sticker::Sticker() :
    transformHandler(new TransformHandler(this))
{
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    transformHandler->setVisible(false);
}

Sticker::~Sticker()
{
    delete transformHandler;
}

void Sticker::setPos(const QPointF &pos)
{
    QGraphicsItem::setPos(pos - boundingRect().center());
}


void Sticker::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
    QGraphicsItem::mousePressEvent(event);
}

void Sticker::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant Sticker::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemSelectedChange) {
        if(value == true)
            transformHandler->setVisible(true);
        else
            transformHandler->setVisible(false);
    }

    return QGraphicsItem::itemChange(change, value);
}
