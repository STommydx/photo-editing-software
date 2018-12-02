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
    mode(Mode::penMode),
    pathSticker(nullptr)
{
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    setImage(QImage(DEFAULT_PHOTO));
}

/**
 * @brief Sets the background and foreground to the given image
 *
 * The function first scales the image to fit the scene.
 * Then, it applys all the image filter to the image.
 * Lastly, it blurs the background for three times using mean blur.
 *
 * The function reproduces a background and forground scene with a effect similar to Instagram.
 *
 * @param image the image to be set
 */
void EditorGraphicsScene::setImage(const QImage &image)
{
    if (image.isNull()) return;
    this->image = image;

    // Background unprocessed image
    QImage &&enlargedImage = image.scaled(SCENE_WIDTH, SCENE_HEIGHT, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QImage &&choppedImage = enlargedImage.copy(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    // Foreground unprocessed image
    QImage &&scaledImage = image.scaled(SCENE_WIDTH, SCENE_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Setup progress dialog
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

        if (background) { removeItem(background); delete background; }
        background = addPixmap(QPixmap::fromImage(processedImage));
        background->setTransformationMode(Qt::SmoothTransformation);
        background->setZValue(BACKGROUND_Z_VALUE);
    }

    if (foreground) { removeItem(foreground); delete foreground; }
    foreground = addPixmap(QPixmap::fromImage(scaledImage));
    foreground->setTransformationMode(Qt::SmoothTransformation);
    foreground->setPos({SCENE_WIDTH / 2.0 - scaledImage.width() / 2.0, SCENE_HEIGHT / 2.0 - scaledImage.height() / 2.0});
    foreground->setZValue(FOREGROUND_Z_VALUE);
}

/**
 * @brief Returns an image snapshot of the current scene
 * @return an image snapshot if the current scene
 */
QImage EditorGraphicsScene::createSnapshot()
{
    QImage img(SCENE_WIDTH, SCENE_HEIGHT, QImage::Format_ARGB32_Premultiplied); // construct empty image
    QPainter qp;
    qp.begin(&img);
    render(&qp); // render the scene to the image
    qp.end();
    return img;
}

/**
 * @brief Applys the specified @a filter with specified size and strength option
 * @param filter the pointer to the filter
 * @param size the size option
 * @param strength the strength option, scaled for @c 0.0 to @c 1.0
 */
void EditorGraphicsScene::applyEffect(ImageFilter *filter, int size, double strength)
{
    applyEffectList.append({filter, {size, strength}}); // add the effect to the list
    setImage(image); // regenerate background and foreground
}

/**
 * @brief Clears all effects previously applied.
 */
void EditorGraphicsScene::clearEffect()
{
    applyEffectList.clear(); // clear the effect list
    setImage(image); // regenerate background and foreground
}

/**
 * @brief Set the path of the selected sticker
 * @param value file path to a svg image
 */
void EditorGraphicsScene::setStickerPath(const QString &value) { svgPath = value; }

/**
 * @brief Set the stroke width of the pen tool
 * @param value stroke width
 */
void EditorGraphicsScene::setStrokeWidth(int value) { pen.setWidth(value); }

/**
 * @brief Set the color of the pen tool
 * @param value color of the pen tool
 */
void EditorGraphicsScene::setPenColor(const QColor &value) { pen.setColor(value); }

/**
 * @brief Set canvas mode
 * @param mode @c EditorGraphicsScene::Mode::penMode or @c EditorGraphicsScene::Mode::stickerMode
 */
void EditorGraphicsScene::setMode(EditorGraphicsScene::Mode mode) { this->mode = mode; }

/**
 * @brief Handles canvas behavior on mouse clicked
 * @param event Mouse press event
 *
 * Add svg sticker if current mode is @c EditorGraphicsScene::Mode::stickerMode
 */
void EditorGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Let base class handle mouse event if current mode is not sticker mode or received a right click
    if(mode == Mode::penMode
            || mode == Mode::effectMode
            || event->button() != Qt::RightButton) {
        QGraphicsScene::mousePressEvent(event);
        return;
    }

    // Adds a new sticker
    Sticker<QGraphicsSvgItem> *svgSticker = new Sticker<QGraphicsSvgItem>(svgPath);
    svgSticker->setPos(event->scenePos());
    addSticker(svgSticker);

    QGraphicsScene::mousePressEvent(event);
}

/**
 * @brief Handles canvas behavior on mouse moved
 * @param event Mouse move event
 *
 * Append to pen path or drag sticker depending on current mode and @a event
 */
void EditorGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Let base class handle event if current mode is sticker mode or event is initiated with right click
    if(mode == Mode::stickerMode
            || mode == Mode::effectMode
            || (event->buttons() & Qt::RightButton) == 0) {
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }

    QPainterPath path;
    // If first move event after press event, set current processing pathSticker to a new path sticker
    if(pathSticker == nullptr) {
        path.moveTo(event->scenePos());					// move path to event scene position
        pathSticker = new Sticker<QGraphicsPathItem>();	// create a new path sticker
        pathSticker->setPen(pen);						// set sticker pen to default pen
        pathSticker->setPath(path);						// set sticker path to the new path
        addSticker(pathSticker);						// add sticker to canvas
    }

    path = pathSticker->path();							// get path from sticker
    path.lineTo(event->scenePos());						// draw line from last event pos to current pos
    pathSticker->setPath(path);
    pathSticker->update();

    QGraphicsScene::mouseMoveEvent(event);
}

/**
 * @brief Returns the original unprocessed image of the scene
 * @return original unprocessed image
 */
QImage EditorGraphicsScene::getImage() const
{
    return image;
}

/**
 * @brief Handles behavior of canvas when mouse released
 * @param event Mouse release event
 *
 * Set current processing path sticker to nullptr if current mode is pen mode
 */
void EditorGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(mode == Mode::penMode)
        pathSticker = nullptr;
    QGraphicsScene::mouseReleaseEvent(event);
}

/**
 * @brief Delete selected item
 */
void EditorGraphicsScene::deleteSelected()
{
    QGraphicsItem* item = selectedItems().first();
    removeItem(item);
    delete item;
}

/**
 * @brief Bring selected item to top in canvas
 */
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
