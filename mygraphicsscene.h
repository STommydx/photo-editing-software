#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QImage>
#include <QVector>
#include <QPair>
#include <vector>

#include "sticker.h"
#include "filtereffect.h"

using std::vector;

class MyGraphicsScene : public QGraphicsScene
{
public:
    MyGraphicsScene(QObject *parent = nullptr);
    vector<Sticker*> items;
    void addSticker(Sticker *sticker);
    void undo();
    void setImage(const QImage &image);
    QImage getImage() const;
    QImage *createSnapshot();
    void applyEffect(const FilterEffect &filter, int size, double strength);
    void clearEffect();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;

private:
    static const int SCENE_WIDTH = 1080;
    static const int SCENE_HEIGHT = 1920;
    static const QString DEFAULT_PHOTO;
    QImage image;
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *foreground;
    QVector<QPair<FilterEffect, QPair<int, double>>> applyEffectList;
};

#endif // MYGRAPHICSSCENE_H
