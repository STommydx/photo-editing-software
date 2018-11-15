#include "mygraphicsscene.h"
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QFont>


#include "svgsticker.h"
#include "textsticker.h"

MyGraphicsScene::MyGraphicsScene(QObject *parent) : QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT, parent), background(nullptr)
{

}

void MyGraphicsScene::undo()
{
    if (items.empty()) return;
    Sticker* sticker = items.back();
    items.pop_back();
    removeItem(sticker);
    delete sticker;
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QFont font;
    font.setPixelSize(64);

    Sticker* item = nullptr;

    if(event->button() == Qt::MiddleButton)
    {
        item = new SvgSticker(":/assets/img/bjarne-stroustrup.svg");
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

void MyGraphicsScene::setImage(const QImage &image)
{
    if (background) removeItem(background);
    background = addPixmap(QPixmap::fromImage(image).scaledToWidth(1080));
    background->setTransformationMode(Qt::SmoothTransformation);
}
