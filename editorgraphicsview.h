#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>

class EditorGraphicsView : public QGraphicsView
{

public:
    EditorGraphicsView(QWidget *parent = nullptr);

protected:
    virtual void resizeEvent(QResizeEvent *) override;    
};

#endif // MYGRAPHICSVIEW_H
