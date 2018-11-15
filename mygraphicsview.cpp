#include "mygraphicsview.h"
#include <QDebug>

MyGraphicsView::MyGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    setInteractive(true);
}

void MyGraphicsView::resizeEvent(QResizeEvent *event) {
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}

