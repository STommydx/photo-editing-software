#ifndef COLORDISPLAY_H
#define COLORDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>

class ColorDisplay : public QGraphicsView
{
public:
    ColorDisplay(QColor color = Qt::black, QWidget *parent = nullptr);
    ColorDisplay(QWidget *parent);
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    QColor color;
};

#endif // COLORDISPLAY_H
