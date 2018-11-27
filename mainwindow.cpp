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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new StickerThumbnailsModel(this)),
    delegate(new StickerThumbnailsDelegate(this))
{
    ui->setupUi(this);
    ui->stickerToolbar->hide();

    // Sticker tab
    QTableView *tableView = ui->stickerTableView;
    int width = tableView->width()/2.2;

    tableView->setShowGrid(false);
    tableView->horizontalHeader()->hide();
    tableView->verticalHeader()->hide();
    tableView->verticalHeader()->setDefaultSectionSize(width);
    tableView->horizontalHeader()->setDefaultSectionSize(width);

    tableView->setModel(model);
    tableView->setItemDelegate(delegate);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setCurrentIndex(model->index(0,0));

    // Graphics scene
    gps = new MyGraphicsScene(this);
    gps->setStickerPath(model->index(0,0).data().toString());
    gps->setImage(QImage(":assets/img/timetable.png"));
    gps->setPenColor(ui->penColor->getColor());
    gps->setStrokeWidth(ui->penSlider->value());
    ui->graphicsView->setScene(gps);

    connect(gps, SIGNAL(selectionChanged()), this, SLOT(m_on_gps_selectionChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionTest_triggered()
{
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

    TestSticker<QGraphicsTextItem> *textSticker =
            new TestSticker<QGraphicsTextItem>(ui->textEdit->text());

    textSticker->get().setFont(font);
    textSticker->get().setDefaultTextColor(color);
    textSticker->updateGeometry();

    gps->addSticker(textSticker);
}

void MainWindow::on_horizontalSlider_valueChanged(int x)
{
    ui->spinBox->setValue(x);
}

void MainWindow::on_spinBox_valueChanged(int x)
{
    ui->horizontalSlider->setValue(x);
}

void MainWindow::on_penSlider_valueChanged(int x)
{
    ui->penSpinner->setValue(x);
    gps->setStrokeWidth(x);
}

void MainWindow::on_penSpinner_valueChanged(int x)
{
    ui->penSlider->setValue(x);
    gps->setStrokeWidth(x);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Import Image from File System", QString(), "Images (*.png *.xpm *.jpg)");
    QImage image{fileName};
    gps->setImage(image);
}

void MainWindow::on_penColor_colorChanged(QColor color)
{
    gps->setPenColor(color);
}

void MainWindow::on_actionDelete_triggered()
{
    gps->deleteSelected();
}

void MainWindow::on_actionToFront_triggered()
{
    gps->bringToFrontSelected();
}

void MainWindow::on_actionToBack_triggered()
{
    gps->sendToBackSelected();
}

void MainWindow::m_on_gps_selectionChanged()
{
    QList<QGraphicsItem *> selections = gps->selectedItems();
    if(selections.isEmpty())
        ui->stickerToolbar->hide();
    else
        ui->stickerToolbar->show();
}

void MainWindow::on_tabWidget_currentChanged(int tab)
{
    if(tab == TAB_PEN)
        gps->setMode(MyGraphicsScene::Mode::Pen);
    else if(tab == TAB_STICKER)
        gps->setMode(MyGraphicsScene::Mode::Sticker);
}

void MainWindow::on_stickerTableView_clicked(const QModelIndex &index)
{
    gps->setStickerPath(index.data().toString());
}
