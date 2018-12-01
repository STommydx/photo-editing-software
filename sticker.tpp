#ifndef STICKER_TPP
#define STICKER_TPP

#include "sticker.h"

template<typename T>
template<typename ...Args>
Sticker<T>::Sticker(Args... args) :
    T(args...),
    resizeAnchor(this, Anchor::RESIZE)
{

    QRectF rect = this->boundingRect();
    QSizeF size = rect.size();

    this->setCursor(Qt::OpenHandCursor);
    this->setAcceptedMouseButtons(Qt::LeftButton);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    if(dynamic_cast<QGraphicsSvgItem*>(this) != nullptr
            && qMin(size.height(), size.width()) < MIN_SIZE) {
        size.scale(MIN_SIZE, MIN_SIZE, Qt::KeepAspectRatio);
        qreal scale = size.width() / rect.width();
        this->setScale(scale);
    }
}

template<typename T>
Sticker<T>::~Sticker()
{
}

template<typename T>
QVariant Sticker<T>::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemSelectedHasChanged)
    {
        resizeAnchor.setVisible(this->isSelected());
        resizeAnchor.setPos(this->boundingRect().topLeft());
    }
    if(change == QGraphicsItem::ItemScaleHasChanged)
    {
        this->setTransformOriginPoint(this->boundingRect().bottomRight());
        this->resizeAnchor.setPos(this->boundingRect().topLeft());
    }
    return T::itemChange(change, value);
}

#endif // STICKER_TPP
