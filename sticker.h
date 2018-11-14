#ifndef STICKER_H
#define STICKER_H

#include <QObject>
#include <QWidget>

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

//template<typename T, typename std::enable_if<std::is_base_of<QGraphicsItem, T>::value>::type* = nullptr>
class Sticker : public QGraphicsItem
{
public:
    Sticker();
    void setPos(const QPointF& pos);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
//    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // STICKER_H
