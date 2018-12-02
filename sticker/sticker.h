#ifndef STICKER_H
#define STICKER_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsSvgItem>

#include "anchor.h"

template<typename T>
class Sticker : public T
{

public:
    template<typename ...Args>
    Sticker(Args... args);
    virtual ~Sticker();

protected:
    virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

private:
    /**
     * @brief minimum default size of a svg sticker
     */
    static const int MIN_SIZE = 200;
    Anchor resizeAnchor;
};

#include "sticker.tpp"

#endif // STICKER_H

