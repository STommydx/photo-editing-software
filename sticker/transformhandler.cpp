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

void TransformHandler::dragScale(QPointF point)
{
    QRectF tmpRect = rect();
    tmpRect.setTopLeft(point);

    QSizeF size(rect().width(), rect().height());
    size.scale(tmpRect.width(), tmpRect.height(), Qt::KeepAspectRatioByExpanding);
    qreal scale = parentItem()->scale() * (size.width() / rect().width());

    if(scale > minScale) {
        parentItem()->setTransformOriginPoint(rect().bottomRight());
        parentItem()->setScale(scale);
    }
}
