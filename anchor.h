#ifndef ANCHOR_H
#define ANCHOR_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QRectF>

class Anchor : public QGraphicsRectItem
{
public:
    static const int RESIZE = 0;
    static const int ROTATE = 1;
    Anchor(QGraphicsItem* parent, int type);
    virtual ~Anchor();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    static const int RADIUS = 8;
    constexpr static const double MIN_SCALE = 0.2;
    const int type;
    void dragScale(QPointF scenePos);
    void dragRotate(QPointF pos);
};


#endif // ANCHOR_H
