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
    if(event->buttons() & Qt::RightButton) {

        if(lastPoint.isNull()) {
            lastPoint = event->scenePos();
            return;
        }

        QPointF endPoint = event->scenePos();

        QPen pen = QPen(penColor, strokeWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        addLine(lastPoint.x(), lastPoint.y(), endPoint.x(), endPoint.y(), pen);

        lastPoint = endPoint;
    }
    else
        QGraphicsScene::mouseMoveEvent(event);
}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    lastPoint = QPoint(0,0);
}

void MyGraphicsScene::setPenColor(const QColor &value)
{
    penColor = value;
}

Sticker *MyGraphicsScene::getSelected()
{
    if(!selectedItems().empty())
        return dynamic_cast<Sticker*>(selectedItems().first());
    else
        return nullptr;
}

void MyGraphicsScene::deleteSelected()
{
    Sticker* sticker = getSelected();
    if(sticker != nullptr)
        delete sticker;
}

// copied from http://doc.qt.io/qt-5/qtwidgets-graphicsview-diagramscene-example.html
void MyGraphicsScene::bringToFrontSelected()
{
    if(selectedItems().isEmpty()) return;

    QGraphicsItem *selectedItem = selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() >= zValue /*&& item->type() == DiagramItem::Type*/)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);
}


void MyGraphicsScene::sendToBackSelected()
{
    if(selectedItems().isEmpty()) return;

    QGraphicsItem *selectedItem = selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue /*&& item->type() == DiagramItem::Type*/)
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}

void MyGraphicsScene::setStrokeWidth(int value)
{
    strokeWidth = value;
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
