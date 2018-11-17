#ifndef STICKER_H
#define STICKER_H

#include <QObject>
#include <QWidget>

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "transformhandler.h"

class TransformHandler;

class Sticker : public QGraphicsItem
{
public:
    Sticker();
    virtual ~Sticker();
    void setPos(const QPointF& pos);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    TransformHandler* transformHandler;
};

#endif // STICKER_H
