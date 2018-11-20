#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QFileDialog>

#include "mygraphicsscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->graphicsView);

    gps = new MyGraphicsScene;
    ui->graphicsView->setScene(gps);

    QImage inp(":assets/img/timetable.png");
    gps->setImage(inp);
}

void MainWindow::on_actionTest_triggered() {
    gps->undo();
}

void MainWindow::on_actionSave_triggered()
{
    QImage *snapshot = gps->createSnapshot();
    snapshot->save("output.png");
    delete snapshot;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Import Image from File System");
    QImage image{fileName};
    gps->setImage(image);
}

MainWindow::~MainWindow()
{
    delete ui;
}
