/**
  * @class Anchor
  *
  * @brief The box that is used to transform a sticker.
  *
  * User can drag the anchor at the corners of a sticker to resize or rotate it
  */

#include "anchor.h"

/**
 * @brief Construct an anchor with an @a parent item.
 * @param parent Parent of this anchor
 * @param type Type of this anchor, could be RESIZE=0 or ROTATE=1
 *
 * Construct an anchor and set its default flags and states,
 * the anchor is defaulted to be at the top left corner of a sticker
 */
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

/**
 * @brief Handles the behavior of itself and its parents when clicke
 * @param event The mouse press event
 */
void Anchor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    parentItem()->setVisible(true);
    event->accept();
}

/**
 * @brief Handles the behavior of parent sticker when dragged
 * @param event The mouse drag event
 *
 * Calls to appropriate handler function according to the type of this anchor.
 * Afterwards, consume the mouse event such that it will not be propagated to underlying graphics items.
 */
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

/**
 * @brief Handles scaling of parent sticker when dragged
 * @param scenePos the pos where the drag event took place
 */
void Anchor::dragScale(QPointF scenePos)
{
    QRectF rect0, rect1;
    rect0 = rect1 = parentItem()->sceneBoundingRect();	// get scene bounding rect of parent sticker
    rect1.setTopLeft(scenePos);							// resize rect1 by setting its top left corner to scenePos
    QSizeF size(rect0.width(), rect0.height());			// retrieve size of the original bounding rect
    size.scale(rect1.width(), rect1.height(), Qt::KeepAspectRatioByExpanding);	// scale the original bounding rect's size to rect1's while maintaining aspect ratio
    qreal scale1 = parentItem()->scale() * (size.width() / rect0.width());	// get new scale
    if(scale1 > MIN_SCALE)	// if new scale is larger than minimum scale, set parent sticker to this new scale
        parentItem()->setScale(scale1);
}

void Anchor::dragRotate(QPointF pos) { /* TODO */ }
