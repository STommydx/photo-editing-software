#include "transformhandler.h"

TransformHandler::TransformHandler(Sticker *parent) :
    QGraphicsRectItem(parent)
{
}

TransformHandler::~TransformHandler()
{
    if(anchor != nullptr) delete anchor;
}

void TransformHandler::init()
{
    setRect(parentItem()->boundingRect());
    anchor = new Anchor(this);
}

#include <QDebug>

void TransformHandler::dragScale(QPointF scenePos)
{
    QRectF rect0 = mapToScene(rect()).boundingRect();
    QRectF rect1 = rect0;
    rect1.setTopLeft(scenePos);

    QSizeF size(rect0.width(), rect0.height());
    size.scale(rect1.width(), rect1.height(), Qt::KeepAspectRatioByExpanding);

    qreal scale = parentItem()->scale() * (size.width() / rect0.width());

    if(scale > minScale) {
        parentItem()->setTransformOriginPoint(rect().bottomRight());
        parentItem()->setScale(scale);
    }


}
