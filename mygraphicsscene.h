#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <vector>
#include "sticker.h"

using std::vector;

class MyGraphicsScene : public QGraphicsScene
{
public:
    MyGraphicsScene(QObject *parent = nullptr);
    vector<Sticker*> items;
    void undo();
    void setImage(const QImage &image);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;

private:
    static const int SCENE_WIDTH = 1080;
    static const int SCENE_HEIGHT = 1920;
    QGraphicsPixmapItem *background;

};

#endif // MYGRAPHICSSCENE_H
