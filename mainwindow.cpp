#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QTableView>

#include "mygraphicsscene.h"
#include "textsticker.h"
#include "svgsticker.h"
#include "stickerthumbnailsview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // setCentralWidget(ui->graphicsView);

    gps = new MyGraphicsScene(this);
    ui->graphicsView->setScene(gps);
    connect(gps, SIGNAL(clicked(QPointF)), this, SLOT(processGraphicsSceneEvent(QPointF)));

    QImage inp(":assets/img/timetable.png");
    gps->setImage(inp);

    initStickerTab();
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

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getStickerPath()
{
    QModelIndex index = ui->stickersPreviewWidget->currentIndex();
    return index.data().toString();
}

void MainWindow::processGraphicsSceneEvent(QPointF scenePos)
{
    SvgSticker* sticker = new SvgSticker(getStickerPath());
    sticker->setPos(scenePos);
    gps->addSticker(sticker);
}

void MainWindow::initStickerTab()
{
    model = new StickerThumbnailsModel(this);
    delegate = new StickerThumbnailsDelegate(this);

    QTableView *tableView = ui->stickersPreviewWidget;

    tableView->setShowGrid(false);
    tableView->horizontalHeader()->hide();
    tableView->verticalHeader()->hide();

    tableView->setModel(model);
    tableView->setItemDelegate(delegate);

    int width = tableView->width()/2.2;
    tableView->verticalHeader()->setDefaultSectionSize(width);
    tableView->horizontalHeader()->setDefaultSectionSize(width);

    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setCurrentIndex(model->index(0,0));

}
