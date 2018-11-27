#include "mygraphicsscene.h"
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QFont>
#include <QPainter>
#include <QImage>

#include "svgsticker.h"
#include "textsticker.h"
#include "imageutil.h"

const QString MyGraphicsScene::DEFAULT_PHOTO = ":/assets/img/default.png";

MyGraphicsScene::MyGraphicsScene(QObject *parent) :
    QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT, parent),
    background(nullptr),
    foreground(nullptr)
{
    setImage(QImage(DEFAULT_PHOTO));
}

void MyGraphicsScene::addSticker(Sticker *item)
{
    if (item != nullptr) {
        addItem(item);
        items.push_back(item);
    }
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

    addSticker(item);
    if (item) item->setPos(event->scenePos());

    QGraphicsScene::mousePressEvent(event);
}

void MyGraphicsScene::setImage(const QImage &image)
{
    this->image = image;
    if (image.isNull()) return;
    if (background) removeItem(background);
    if (foreground) removeItem(foreground);

    QImage &&enlargedImage = image.scaled(SCENE_WIDTH, SCENE_HEIGHT, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QImage &&choppedImage = enlargedImage.copy(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    QImage &&processedImage = ImageUtil::multipassMeanBlur(choppedImage, 40);
    background = addPixmap(QPixmap::fromImage(processedImage));
    background->setTransformationMode(Qt::SmoothTransformation);

    QImage &&scaledImage = image.scaled(SCENE_WIDTH, SCENE_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    foreground = addPixmap(QPixmap::fromImage(scaledImage));
    foreground->setTransformationMode(Qt::SmoothTransformation);
    foreground->setPos({SCENE_WIDTH / 2.0 - scaledImage.width() / 2.0, SCENE_HEIGHT / 2.0 - scaledImage.height() / 2.0});
}

QImage MyGraphicsScene::getImage() const
{
    return image;
}

QImage *MyGraphicsScene::createSnapshot()
{
    QImage *img = new QImage(SCENE_WIDTH, SCENE_HEIGHT, QImage::Format_ARGB32_Premultiplied);
    QPainter qp;
    qp.begin(img);
    render(&qp);
    qp.end();
    return img;
}
