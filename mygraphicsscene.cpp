#include "mygraphicsscene.h"
#include <QGraphicsTextItem>
#include <QGraphicsSvgItem>
#include <QGraphicsPathItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QFont>
#include <QPainter>
#include <QImage>

#include "teststicker.h"
#include "imageutil.h"

const QString MyGraphicsScene::DEFAULT_PHOTO = ":/assets/img/default.png";

MyGraphicsScene::MyGraphicsScene(QObject *parent) :
    QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT, parent),
    background(nullptr),
    foreground(nullptr),
    isSelecting(false),
    pathSticker(nullptr),
    mode(Mode::Sticker)
{
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));

    setImage(QImage(DEFAULT_PHOTO));
}

MyGraphicsScene::~MyGraphicsScene() { /* TODO */ }

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
        pathSticker->setPen(pen);
        pathSticker->setPath(path);
        addSticker(pathSticker);
    }

    path = pathSticker->path();
    path.lineTo(event->scenePos());
    pathSticker->setPath(path);
    pathSticker->update();

    QGraphicsScene::mouseMoveEvent(event);
}

QImage MyGraphicsScene::getImage() const
{
    return image;
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
        removeItem(selectedItems().first());
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

