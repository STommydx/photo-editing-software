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

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;

};

#endif // MYGRAPHICSSCENE_H
