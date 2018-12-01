#ifndef COLORDISPLAY_H
#define COLORDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>

class ColorDisplay : public QGraphicsView
{
    Q_OBJECT

public:
    ColorDisplay(QColor color = Qt::black, QWidget *parent = nullptr);
    ColorDisplay(QWidget *parent);
    virtual ~ColorDisplay();
    virtual void mousePressEvent(QMouseEvent *event) override;

    QColor getColor() const;

private:
    QColor color;

signals:
    void colorChanged(QColor color);
};

#endif // COLORDISPLAY_H
