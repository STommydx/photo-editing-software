#ifndef ANCHOR_H
#define ANCHOR_H

#include <QGraphicsRectItem>
#include <QRectF>

#include "transformhandler.h"

class TransformHandler;

class Anchor : public QGraphicsRectItem
{
public:
    Anchor(TransformHandler* parent);
    virtual ~Anchor();

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    static const int RADIUS = 8;



};

#endif // ANCHOR_H
