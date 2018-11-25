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


    void setStrokeWidth(int value);
    void setPenColor(const QColor &value);

    Sticker* getSelected();
    void deleteSelected();
    void bringToFrontSelected();
    void sendToBackSelected();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    static const int SCENE_WIDTH = 1080;
    static const int SCENE_HEIGHT = 1920;
    QGraphicsPixmapItem *background;

    //
    QPointF lastPoint;
    int strokeWidth;
    QColor penColor;

signals:
    void clicked(QPointF);

};

#endif // MYGRAPHICSSCENE_H
