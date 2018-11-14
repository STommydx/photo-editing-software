#include "mygraphicsscene.h"
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QFont>


#include "svgsticker.h"
#include "textsticker.h"

MyGraphicsScene::MyGraphicsScene(QObject *parent) : QGraphicsScene(0, 0, 1080, 1920, parent)
{

}

void MyGraphicsScene::undo()
{
    Sticker* sticker = items.back();
    items.pop_back();
    removeItem(sticker);
    delete sticker;
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    // qDebug() << "wtf" << endl;
    QFont font;
    font.setPixelSize(64);

    Sticker* item = nullptr;

    if(event->button() == Qt::MiddleButton)
    {
        item = new SvgSticker(":/img/bjarne-stroustrup.svg");
    }
    else if(event->button() == Qt::RightButton)
    {
        item = new TextSticker("Hello World");
    }

    if(item != nullptr) {
        addItem(item);
        item->setPos(event->scenePos());
        items.push_back(item);
    }

    QGraphicsScene::mousePressEvent(event);
}
