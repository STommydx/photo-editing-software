#include "colordisplay.h"
#include <QColorDialog>

ColorDisplay::ColorDisplay(QColor color, QWidget *parent) :
    QGraphicsView{parent},
    color{color}
{
    setScene(new QGraphicsScene);
    QBrush brush{color};
    setBackgroundBrush(brush);
}

ColorDisplay::ColorDisplay(QWidget *parent) :
    ColorDisplay(Qt::black, parent)
{
}

ColorDisplay::~ColorDisplay()
{
    delete scene();
}

void ColorDisplay::mousePressEvent(QMouseEvent *)
{
    color = QColorDialog::getColor(color, this, "Color Picker");
    QBrush brush{color};
    setBackgroundBrush(brush);
    emit colorChanged(color);
}

QColor ColorDisplay::getColor() const
{
    return color;
}
