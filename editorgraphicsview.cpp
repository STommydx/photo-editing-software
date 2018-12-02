/**
 * @class EditorGraphicsView
 * @brief The EditorGraphicsView class provides a widget for viewing the EditorGraphicsScene.
 */

#include "editorgraphicsview.h"

/**
 * @brief Constructs a viewing widget with the given parent
 * @param parent the parent widget
 */
EditorGraphicsView::EditorGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    setInteractive(true);
}

/**
 * @brief Handles the action when the user resize the view or its parent
 * @param event the resize event
 */
void EditorGraphicsView::resizeEvent(QResizeEvent *event) {
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}
