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

#include "teststicker.h"
#include "filter/imagefilter.h"

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MyGraphicsScene(QObject *parent = nullptr);
    virtual ~MyGraphicsScene();
    void undo();
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
    static const int SCENE_WIDTH = 1080;
    static const int SCENE_HEIGHT = 1920;
    static const QString DEFAULT_PHOTO;
    QImage image;
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *foreground;
    QVector<QPair<ImageFilter*, QPair<int, double>>> applyEffectList;

// Sticker mode and options
public:
    enum Mode { Pen, Sticker };

    template<typename T>
    void addSticker(TestSticker<T> *sticker);
    void setMode(MyGraphicsScene::Mode mode);
    void setStrokeWidth(int value);
    void setPenColor(const QColor &value);
    void deleteSelected();
    void bringToFrontSelected();
    void sendToBackSelected();
    void setStickerPath(const QString &value);

private:
    Mode mode;
    bool isSelecting;
    TestSticker<QGraphicsPathItem>* pathSticker;
    QPen pen;
    QString svgPath;

private slots:
    void onSelectionChanged();

};

template<typename T>
void MyGraphicsScene::addSticker(TestSticker<T> *sticker)
{
    addItem(sticker);
}

#endif // MYGRAPHICSSCENE_H
