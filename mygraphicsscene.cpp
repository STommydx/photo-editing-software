#include "mygraphicsscene.h"
#include <QGraphicsTextItem>
#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QFont>
#include <QPainter>
#include <QImage>

#include "teststicker.h"

MyGraphicsScene::MyGraphicsScene(QObject *parent) :
    QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT, parent),
    background(nullptr),
    pathSticker(nullptr),
    isSelecting(false),
    mode(Mode::Sticker)
{
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
}

MyGraphicsScene::~MyGraphicsScene() { /* TODO */ }

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

/* Sticker build options */

void MyGraphicsScene::setStickerPath(const QString &value) { svgPath = value; }

void MyGraphicsScene::setStrokeWidth(int value) { pen.setWidth(value); }

void MyGraphicsScene::setPenColor(const QColor &value) { pen.setColor(value); }

void MyGraphicsScene::setMode(MyGraphicsScene::Mode mode) { this->mode = mode; }

/* Process sticker actions */

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(mode == Mode::Pen || event->button() != Qt::RightButton) {
        QGraphicsScene::mousePressEvent(event);
        return;
    }

    TestSticker<QGraphicsSvgItem> *svgSticker = new TestSticker<QGraphicsSvgItem>(svgPath);
    svgSticker->setPos(event->scenePos());
    addSticker(svgSticker);

    QGraphicsScene::mousePressEvent(event);
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(mode == Mode::Sticker || (event->buttons() & Qt::RightButton) == 0) {
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }

    QPainterPath path;
    if(pathSticker == nullptr) {
        path.moveTo(event->scenePos());
        pathSticker = new TestSticker<QGraphicsPathItem>();
        pathSticker->get().setPen(pen);
        pathSticker->get().setPath(path);
        addSticker(pathSticker);
    }

    path = pathSticker->get().path();
    path.lineTo(event->scenePos());
    pathSticker->get().setPath(path);
    pathSticker->updateGeometry();

    QGraphicsScene::mouseMoveEvent(event);
}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(mode == Mode::Pen)
        pathSticker = nullptr;
    QGraphicsScene::mouseReleaseEvent(event);
}

void MyGraphicsScene::onSelectionChanged()
{
    isSelecting = !selectedItems().isEmpty();
}

/* Sticker toolbar */
void MyGraphicsScene::deleteSelected()
{
    if(!selectedItems().isEmpty())
        delete selectedItems().first();
}

void MyGraphicsScene::bringToFrontSelected()
{
    if(selectedItems().isEmpty()) return;
    QGraphicsItem* selected = selectedItems().first();
    qreal zValue = 0;
    for(QGraphicsItem *item : selected->collidingItems()) {
        if (item->zValue() >= zValue)
            zValue = item->zValue() + 0.1;
    }
    selected->setZValue(zValue);
}

void MyGraphicsScene::sendToBackSelected()
{
    if(selectedItems().isEmpty()) return;
    QGraphicsItem* selected = selectedItems().first();
    qreal zValue = 0;
    for(QGraphicsItem *item : selected->collidingItems()) {
        if (item->zValue() <= zValue)
            zValue = item->zValue() - 0.1;
    }
    selected->setZValue(zValue);
}

void MyGraphicsScene::undo()
{
}

