#ifndef ANCHOR_H
#define ANCHOR_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QRectF>

#include "teststicker.h"

class Anchor : public QGraphicsRectItem
{
public:
    static const int RESIZE = 0;
    static const int ROTATE = 1;
    Anchor(QGraphicsItem* parent, int type) :
        QGraphicsRectItem(-RADIUS, -RADIUS, RADIUS*2, RADIUS*2, parent),
        type(type)
    {
        setFlag(QGraphicsItem::ItemIsSelectable);
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemIgnoresTransformations);
    }
    virtual ~Anchor() {}

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override
    {
        switch(type)
        {
            case RESIZE:
                dragScale(event->scenePos()); break;
            case ROTATE:
                dragRotate(event->scenePos()); break;
        }
        event->accept();
    }

private:
    static const int RADIUS = 8;
    const int type;
    void dragScale(QPointF scenePos)
    {
        QRectF rect0, rect1;
        rect0 = rect1 = parentItem()->sceneBoundingRect();
        rect1.setTopLeft(scenePos);
        QSizeF size(rect0.width(), rect0.height());
        size.scale(rect1.width(), rect1.height(), Qt::KeepAspectRatioByExpanding);
        qreal scale1 = parentItem()->scale() * (size.width() / rect0.width());
        parentItem()->setScale(scale1);
    }
    void dragRotate(QPointF pos)
    {
        static QPointF lastPoint;
        if(lastPoint.isNull())
            lastPoint = pos;
    }
};

#endif // ANCHOR_H
