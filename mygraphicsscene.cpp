#include "mygraphicsscene.h"
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QFont>
#include <QPainter>
#include <QImage>

#include "svgsticker.h"
#include "textsticker.h"

MyGraphicsScene::MyGraphicsScene(QObject *parent) :
    QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT, parent),
    background(nullptr),
    lastPoint(QPointF(0,0))
{
}

MyGraphicsScene::~MyGraphicsScene()
{
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
    if(event->button() == Qt::MiddleButton) {
        emit clicked(event->scenePos());
    }

    QGraphicsScene::mousePressEvent(event);
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qInfo() << "Start drawing";
    if(event->buttons() & Qt::RightButton) {

    if(lastPoint.isNull()) {
        lastPoint = event->scenePos();
//        qInfo() << event->pos();
//        qInfo() << event->scenePos();
        return;
    }
    qInfo() << lastPoint;

    QPointF endPoint = event->scenePos();
    QPointF ctrlPoint = (lastPoint + endPoint) / 2;

    QPainterPath painterPath(lastPoint);
    painterPath.quadTo(ctrlPoint, endPoint);

    QPen pen = QPen(Qt::blue, 24, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    addPath(painterPath, pen);
//    addLine(lastPoint.x(), lastPoint.y(), endPoint.x(), endPoint.y(), pen);

    lastPoint = endPoint;

    }

}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    lastPoint = QPoint(0,0);
}

void MyGraphicsScene::setImage(const QImage &image)
{
    if (background) removeItem(background);
    background = addPixmap(QPixmap::fromImage(image.scaledToWidth(SCENE_WIDTH, Qt::SmoothTransformation)));
    background->setTransformationMode(Qt::SmoothTransformation);
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
