#ifndef TESTSTICKER_H
#define TESTSTICKER_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsSvgItem>
#include <QDebug>

#include <typeinfo>

#include "anchor.h"

template<typename T>
class TestSticker : public T
{

public:
    template<typename ...Args>
    TestSticker(Args... args) :
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
    virtual ~TestSticker() {}

protected:
    virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override
    {
        qInfo() << change;
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

private:
    static const int RADIUS = 8;
    static const int MIN_SIZE = 200;

    Anchor resizeAnchor;
};

#endif // TESTSTICKER_H

