#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QImage>
#include <QString>
#include <vector>
#include <QPainterPath>
#include <QGraphicsPathItem>

#include "teststicker.h"

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MyGraphicsScene(QObject *parent = nullptr);
    virtual ~MyGraphicsScene();
    void undo();
    void setImage(const QImage &image);
    QImage *createSnapshot();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    static const int SCENE_WIDTH = 1080;
    static const int SCENE_HEIGHT = 1920;
    QGraphicsPixmapItem *background;

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
    bool isSelecting;
    Mode mode;
    QPen pen;
    TestSticker<QGraphicsPathItem>* pathSticker;
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
