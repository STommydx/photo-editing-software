#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QImage>
#include <QString>
#include <vector>
#include "sticker.h"

using std::vector;

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MyGraphicsScene(QObject *parent = nullptr);
    virtual ~MyGraphicsScene();
    vector<Sticker*> items;
    void addSticker(Sticker *sticker);
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

    //
    bool startDraw;
    QPointF lastPoint;
signals:
    void clicked(QPointF);
};

#endif // MYGRAPHICSSCENE_H
