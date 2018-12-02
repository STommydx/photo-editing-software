#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QImage>
#include <QVector>
#include <QPair>
#include <vector>
#include <QString>
#include <QPainterPath>
#include <QGraphicsPathItem>

#include "sticker.h"
#include "filter/imagefilter.h"

class EditorGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    EditorGraphicsScene(QObject *parent = nullptr);
    virtual ~EditorGraphicsScene() override = default;
    void setImage(const QImage &image);
    QImage getImage() const;
    QImage createSnapshot();
    void applyEffect(ImageFilter *filter, int size, double strength);
    void clearEffect();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    static const int SCENE_WIDTH = 1080; /**< @brief The width of the editor */
    static const int SCENE_HEIGHT = 1920; /**< @brief The height of the editor */
    static const double BACKGROUND_Z_VALUE;
    static const double FOREGROUND_Z_VALUE;
    static const QString DEFAULT_PHOTO;
    QImage image; /**< @brief The unmodified background and foreground image */
    QGraphicsPixmapItem *background; /**< @brief The pointer to background image item */
    QGraphicsPixmapItem *foreground; /**< @brief The pointer to foreground image item */
    QVector<QPair<ImageFilter*, QPair<int, double>>> applyEffectList; /**< @brief The list storing the applied filters and options */

// Sticker mode and options
public:
    /**
     * @brief The Mode enum represents the modes of the editor scene
     */
    enum Mode { penMode, stickerMode };

    template<typename T>
    void addSticker(Sticker<T> *sticker);
    void setMode(EditorGraphicsScene::Mode mode);
    void setStrokeWidth(int value);
    void setPenColor(const QColor &value);
    void deleteSelected();
    void bringToFrontSelected();
    void setStickerPath(const QString &value);

private:
    Mode mode; /**< @brief The current mode of the editor */
    Sticker<QGraphicsPathItem>* pathSticker; /**< @brief The currently drawing path sticker */
    QPen pen; /**< @brief Pen for drawing paths */
    QString svgPath; /**< @brief The string representing the location of svg sticker */

};

/**
 * @brief Add @a sticker to the editor scene.
 * @param sticker the sticker to be added to the scene
 */
template<typename T>
void EditorGraphicsScene::addSticker(Sticker<T> *sticker)
{
    addItem(sticker);
}

#endif // MYGRAPHICSSCENE_H
