#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QGraphicsPixmapItem>

#include "mygraphicsscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->graphicsView);

    gps = new MyGraphicsScene;
    ui->graphicsView->setScene(gps);

    gps->addRect(0, 900, 100, 100, QPen(), QBrush(QColor(255, 0, 0, 30)));

    QImage inp(":assets/img/timetable.png");
    gps->addPixmap(QPixmap::fromImage(inp).scaledToWidth(1080))->setTransformationMode(Qt::SmoothTransformation);

    qDebug() << gps->sceneRect() << endl;
}

void MainWindow::on_actionTest_triggered() {
//    QImage img(1080, 1920, QImage::Format_ARGB32_Premultiplied);
//    QPainter qp;
//    qp.begin(&img);
//    ui->graphicsView->scene()->render(&qp);
//    qp.end();
//    img.save("wtf.png");
    gps->undo();
}

MainWindow::~MainWindow()
{
    delete ui;
}
