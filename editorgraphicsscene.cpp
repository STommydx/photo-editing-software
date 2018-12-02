/**
 * @class EditorGraphicsScene
 * @brief The EditorGraphicsScene class provides the editor scene of the image editor.
 *
 * The class handles most of the functionality of the photo editor, including adding stickers, applying filter effects and the pen drawing.
 * It also provides functionality to load images for background and export the current scene image.
 */
#include "editorgraphicsscene.h"
#include <QGraphicsTextItem>
#include <QGraphicsSvgItem>
#include <QGraphicsPathItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QFont>
#include <QPainter>
#include <QImage>
#include <QProgressDialog>
#include <QApplication>

#include "sticker.h"
#include "filter/fastmeanblurfilter.h"

/**
 * @brief Path to default photo
 */
const QString EditorGraphicsScene::DEFAULT_PHOTO = ":/assets/img/default.png";
/**
 * @brief Default z-value of background image
 */
const double EditorGraphicsScene::BACKGROUND_Z_VALUE = -2000.0;
/**
 * @brief Default z-value of foreground image
 */
const double EditorGraphicsScene::FOREGROUND_Z_VALUE = -1000.0;

/**
 * @brief Constructs a graphics scene for photo editing
 * @param parent the parent qobject
 */
EditorGraphicsScene::EditorGraphicsScene(QObject *parent) :
    QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT, parent),
    background(nullptr),
    foreground(nullptr),
    mode(Mode::stickerMode),
    isSelecting(false),
    pathSticker(nullptr)
{
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));

    setImage(QImage(DEFAULT_PHOTO));
}

void EditorGraphicsScene::setImage(const QImage &image)
{
    if (image.isNull()) return;
    this->image = image;

    // Background unprocessed image
    QImage &&enlargedImage = image.scaled(SCENE_WIDTH, SCENE_HEIGHT, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QImage &&choppedImage = enlargedImage.copy(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    // Foreground unprocessed image
    QImage &&scaledImage = image.scaled(SCENE_WIDTH, SCENE_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QProgressDialog progress;
    progress.setMinimumDuration(500);
    progress.setWindowTitle("Applying Filter...");
    progress.setAutoClose(false);

    // Foreground filters
    progress.setMaximum(scaledImage.height());
    for (const QPair<ImageFilter*, QPair<int, double>> &applyFilter : applyEffectList) {
        progress.setLabelText("Applying " + applyFilter.first->getName() + " for foreground...");
        connect(applyFilter.first, &ImageFilter::progressUpdated, &progress, &QProgressDialog::setValue);
        connect(applyFilter.first, &ImageFilter::progressUpdated, [](int){
            QApplication::processEvents();
        });

        scaledImage = (*applyFilter.first)(scaledImage, applyFilter.second.first, applyFilter.second.second);
    }

    // Background processing, only run if foreground does not cover the whole scene
    if (scaledImage.height() != SCENE_HEIGHT || scaledImage.width() != SCENE_WIDTH) {
        // Background filters
        progress.setMaximum(choppedImage.height());
        for (const QPair<ImageFilter*, QPair<int, double>> &applyFilter : applyEffectList) {
            progress.setLabelText("Applying " + applyFilter.first->getName() + " for background...");
            connect(applyFilter.first, &ImageFilter::progressUpdated, &progress, &QProgressDialog::setValue);
            connect(applyFilter.first, &ImageFilter::progressUpdated, [](int){
                QApplication::processEvents();
            });

            choppedImage = (*applyFilter.first)(choppedImage, applyFilter.second.first, applyFilter.second.second);
        }

        // Background blurs
        FastMeanBlurFilter fmbFilter;
        progress.setLabelText("Bluring background...");
        connect(&fmbFilter, &ImageFilter::progressUpdated, &progress, &QProgressDialog::setValue);
        connect(&fmbFilter, &ImageFilter::progressUpdated, []() {
            QApplication::processEvents();
        });
        QImage &&processedImage = fmbFilter(choppedImage, 40, 0, 3);

        if (background) removeItem(background);
        background = addPixmap(QPixmap::fromImage(processedImage));
        background->setTransformationMode(Qt::SmoothTransformation);
        background->setZValue(BACKGROUND_Z_VALUE);
    }

    if (foreground) removeItem(foreground);
    foreground = addPixmap(QPixmap::fromImage(scaledImage));
    foreground->setTransformationMode(Qt::SmoothTransformation);
    foreground->setPos({SCENE_WIDTH / 2.0 - scaledImage.width() / 2.0, SCENE_HEIGHT / 2.0 - scaledImage.height() / 2.0});
    foreground->setZValue(FOREGROUND_Z_VALUE);
}

QImage EditorGraphicsScene::createSnapshot()
{
    QImage img(SCENE_WIDTH, SCENE_HEIGHT, QImage::Format_ARGB32_Premultiplied);
    QPainter qp;
    qp.begin(&img);
    render(&qp);
    qp.end();
    return img;
}

void EditorGraphicsScene::applyEffect(ImageFilter *filter, int size, double strength)
{
    applyEffectList.append({filter, {size, strength}});
    setImage(image);
}

void EditorGraphicsScene::clearEffect()
{
    applyEffectList.clear();
    setImage(image);
}

/* Sticker build options */

void EditorGraphicsScene::setStickerPath(const QString &value) { svgPath = value; }

void EditorGraphicsScene::setStrokeWidth(int value) { pen.setWidth(value); }

void EditorGraphicsScene::setPenColor(const QColor &value) { pen.setColor(value); }

void EditorGraphicsScene::setMode(EditorGraphicsScene::Mode mode) { this->mode = mode; }

/* Process sticker actions */

void EditorGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(mode == Mode::penMode || event->button() != Qt::RightButton) {
        QGraphicsScene::mousePressEvent(event);
        return;
    }

    Sticker<QGraphicsSvgItem> *svgSticker = new Sticker<QGraphicsSvgItem>(svgPath);
    svgSticker->setPos(event->scenePos());
    addSticker(svgSticker);

    QGraphicsScene::mousePressEvent(event);
}

void EditorGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(mode == Mode::stickerMode || (event->buttons() & Qt::RightButton) == 0) {
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }

    QPainterPath path;
    if(pathSticker == nullptr) {
        path.moveTo(event->scenePos());
        pathSticker = new Sticker<QGraphicsPathItem>();
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

QImage EditorGraphicsScene::getImage() const
{
    return image;
}

void EditorGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(mode == Mode::penMode)
        pathSticker = nullptr;
    QGraphicsScene::mouseReleaseEvent(event);
}

void EditorGraphicsScene::onSelectionChanged()
{
    isSelecting = !selectedItems().isEmpty();
}

/* Sticker toolbar */
void EditorGraphicsScene::deleteSelected()
{
    if(!selectedItems().isEmpty())
        removeItem(selectedItems().first());
}

void EditorGraphicsScene::bringToFrontSelected()
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

void EditorGraphicsScene::sendToBackSelected()
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

void EditorGraphicsScene::undo()
{
}

