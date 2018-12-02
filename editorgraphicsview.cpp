#include "editorgraphicsview.h"
#include <QDebug>

EditorGraphicsView::EditorGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    setInteractive(true);
}

void EditorGraphicsView::resizeEvent(QResizeEvent *event) {
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}
