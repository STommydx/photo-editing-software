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
#include "imageutil.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gps(new MyGraphicsScene),
    model(new StickerThumbnailsModel(this)),
    delegate(new StickerThumbnailsDelegate(this)),
    cw(nullptr)
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
    gps->setPenColor(ui->penColor->getColor());
    gps->setStrokeWidth(ui->penSlider->value());
    ui->graphicsView->setScene(gps);
    setupEffectList();

    connect(gps, SIGNAL(selectionChanged()), this, SLOT(m_on_gps_selectionChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gps;
    delete cw;
}

void MainWindow::onActionUndoTriggered()
{
    gps->undo();
}

void MainWindow::on_actionSave_triggered()
{
    QImage *snapshot = gps->createSnapshot();
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image to File System", "untitled.png", "Images (*.png *.xpm *.jpg)");
    snapshot->save(fileName);
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

    TestSticker<QGraphicsTextItem> *textSticker =
            new TestSticker<QGraphicsTextItem>(ui->textEdit->text());

    textSticker->setFont(font);
    textSticker->setDefaultTextColor(color);
//    textSticker->updateGeometry();

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

void MainWindow::onCameraCaptured()
{
    gps->setImage(cw->result());
    delete cw;
    cw = nullptr;
}

void MainWindow::on_effectList_currentRowChanged(int row)
{
    if (row == -1) {
        ui->applyButton->setEnabled(false);
        return;
    }
    ui->applyButton->setEnabled(true);
    FilterEffect &effect = effectList[row];
    ui->effectSizeSlider->setEnabled(effect.sizeEnabled());
    ui->effectSizeSlider->setMaximum(effect.getMaxSize());
    ui->effectStrengthSlider->setEnabled(effect.strengthEnabled());
}

void MainWindow::on_applyButton_clicked()
{
    FilterEffect &filter = effectList[ui->effectList->currentRow()];
    int size = ui->effectSizeSlider->value();
    double strength = ui->effectStrengthSlider->value() / 1000.0;
    gps->applyEffect(filter, size, strength);
}

void MainWindow::on_clearButton_clicked()
{
    gps->clearEffect();
}

void MainWindow::setupEffectList()
{
    effectList.append(FilterEffect{"Grayscale", ImageUtil::grayscale});
    effectList.append(FilterEffect{"Invert", ImageUtil::invert});
    effectList.append(FilterEffect{"Brighten", ImageUtil::brighten, 10.0});
    effectList.append(FilterEffect{"Darken", ImageUtil::darken, 10.0});
    effectList.append(FilterEffect{"Gaussian Blur", ImageUtil::gaussianBlur, 5, 5.0});
    effectList.append(FilterEffect{"Mean Blur", ImageUtil::meanBlur, 5});
    effectList.append(FilterEffect{"Mean Blur (Large Size)", ImageUtil::fastMeanBlur, 100});
    effectList.append(FilterEffect{"Median Blur", ImageUtil::medianBlur, 5});
    effectList.append(FilterEffect{"Sharpen", ImageUtil::sharpen, 5});
    effectList.append(FilterEffect{"Emboss", ImageUtil::emboss, 5});
    effectList.append(FilterEffect{"Pixelize", ImageUtil::pixelize, 100});
    effectList.append(FilterEffect{"Edge Highlight", ImageUtil::edgeDetect, 5});

    for (const FilterEffect &filter : effectList) {
        ui->effectList->addItem(filter.getName());
    }
}
