#ifndef TESTSTICKER_H
#define TESTSTICKER_H

#include <QObject>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QDebug>

#include "anchor.h"

template<typename T>
class TestSticker : public QGraphicsRectItem
{
public:
    template<typename ...Args>
    TestSticker(Args... args) :
        mItem(args...),
        resizeAnchor(&mItem, Anchor::RESIZE)
//        rotateAnchor(&mItem)
    {
        mItem.setParentItem(this);
        mItem.setCursor(Qt::OpenHandCursor);
        mItem.setAcceptedMouseButtons(Qt::LeftButton);
        mItem.setFlag(QGraphicsItem::ItemIsMovable);
        mItem.setFlag(QGraphicsItem::ItemIsSelectable);
        mItem.setTransformOriginPoint(mItem.boundingRect().bottomRight());
    }

    void updateGeometry()
    {
        mItem.setTransformOriginPoint(mItem.boundingRect().bottomRight());
        resizeAnchor.setPos(mItem.boundingRect().topLeft());
//        rotateAnchor.setPos(mItem.boundingRect().topRight());
        update();
    }

    T& get() { return mItem; }
    virtual ~TestSticker() {}

private:
    static const int RADIUS = 8;
    T mItem;
    Anchor resizeAnchor;
//    Anchor rotateAnchor;
};

#endif // TESTSTICKER_H

