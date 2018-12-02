/**
  *	@class Sticker
  * @brief A sticker object
  *
  * This template class defines a sticker object and its control.
  * It takes any class that inherits QGraphicsItem as its template argument,
  * and inherits said QGraphicsItem.
  */

#ifndef STICKER_TPP
#define STICKER_TPP

#include "sticker.h"

/**
 *	@brief Construct a sticker
 *  @param args constructor arguments for type T
 *
 * 	Construct a sticker using argument list for any constructor of type T.
 *  Also initializes its resize anchor
 */
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

    if(dynamic_cast<QGraphicsSvgItem*>(this) != nullptr			// Scales svg stickers if the default size is too small
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

/**
 *	@brief Defines behavior of sticker when its state changes
 *  @param change The type of the change
 *  @param value of the change
 *
 *  Defines the behavior sticker when its selection state or its scale changes
 */
template<typename T>
QVariant Sticker<T>::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemSelectedHasChanged)
    {
        resizeAnchor.setVisible(this->isSelected());			// show anchor when selected
        resizeAnchor.setPos(this->boundingRect().topLeft());	// set anchor pos to top left of sticker
    }
    if(change == QGraphicsItem::ItemScaleHasChanged)
    {
        this->setTransformOriginPoint(this->boundingRect().bottomRight());	// fix position of its bottom right corner
        this->resizeAnchor.setPos(this->boundingRect().topLeft());			// let anchor moves with its top left corner
    }
    return T::itemChange(change, value);
}

#endif // STICKER_TPP
