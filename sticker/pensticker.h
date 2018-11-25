#ifndef PENSTICKER_H
#define PENSTICKER_H

#include "sticker.h"
#include <QGraphicsPathItem>

class PenSticker : public Sticker
{
public:
    PenSticker();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override;
    virtual Sticker::Type getType() const override;
    QPainterPath path();
    void setPath(QPainterPath &path);

    void setPen(const QPen &pen);
private:
    QGraphicsPathItem pathItem;
};

#endif // PENSTICKER_H
