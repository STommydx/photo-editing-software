#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QFileDialog>

#include "mygraphicsscene.h"
#include "textsticker.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gps(new MyGraphicsScene),
    cw(nullptr)
{
    ui->setupUi(this);
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

void MainWindow::on_actionCamera_triggered()
{
    if (cw) return;
    cw = new CameraWindow(this);
    cw->show();
    connect(cw, &CameraWindow::closed, this, &MainWindow::onCameraCaptured);
}

void MainWindow::on_textEnterButton_clicked()
{
    QFont font = ui->fontComboBox->currentFont();
    font.setPointSize(ui->spinBox->value());
    QColor color = ui->textColor->getColor();
    Sticker *sticker = new TextSticker(ui->textEdit->text(), font, color);
    gps->addSticker(sticker);
}

void MainWindow::on_horizontalSlider_valueChanged(int x)
{
    ui->spinBox->setValue(x);
}

void MainWindow::on_penSlider_valueChanged(int x)
{
    ui->penSpinner->setValue(x);
}

void MainWindow::on_spinBox_valueChanged(int x)
{
    ui->horizontalSlider->setValue(x);
}

void MainWindow::on_penSpinner_valueChanged(int x)
{
    ui->penSlider->setValue(x);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Import Image from File System", QString(), "Images (*.png *.xpm *.jpg)");
    QImage image{fileName};
    gps->setImage(image);
}

void MainWindow::onCameraCaptured()
{
    gps->setImage(cw->result());
    delete cw;
    cw = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}
