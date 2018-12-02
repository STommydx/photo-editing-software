/**
 * @class MainWindow
 * @brief The MainWindow class specifies the main window of PES.
 *
 * The main window constructs the necessary widgets and layout for accessing different functionality of the application.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QTableView>
#include <QtMath>

#include "mygraphicsscene.h"
#include "imageutil.h"
#include "exportdialog.h"
#include "sticker.h"

/**
 * @brief Constructs the main window with the given @a parent
 * @param parent the parent widgwt
 *
 * The constructor sets up all necessary components for the main window, including the graphic scene for viewing and editing images.
 * It also initialize the API to the camera and Imgur export.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), // parent class constructor
    ui(new Ui::MainWindow), // instantiate ui
    graphicsScene(new MyGraphicsScene), // instantiate graphics scene for viewing
    model(new StickerThumbnailsModel(this)),
    delegate(new StickerThumbnailsDelegate(this)),
    cw(nullptr), // initialize camera window pointer
    imgur(new ImgurWrapper(this)) // instantiate Imgur API
{
    ui->setupUi(this); // setup UI
    ui->stickerToolbar->hide(); // hide sticker toolbar for later use

    // Sticker tab
    QTableView *tableView = ui->stickerTableView;
    int width = qFloor(tableView->width() / 2.2);

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
    graphicsScene->setStickerPath(model->index(0,0).data().toString());
    graphicsScene->setPenColor(ui->penColor->getColor());
    graphicsScene->setStrokeWidth(ui->penSlider->value());
    ui->graphicsView->setScene(graphicsScene);
    graphicsScene->setParent(ui->graphicsView);

    // Effect list
    for (ImageFilter *filter : effectList) {
        ui->effectList->addItem(filter->getName()); // add each effect in default list to the ui
    }

    connect(graphicsScene, SIGNAL(selectionChanged()), this, SLOT(m_on_gps_selectionChanged()));

    connect(imgur, &ImgurWrapper::imageUploaded, this, &MainWindow::onImageUploaded); // handle image upload signal
}

/**
 * @brief Destructs the main window.
 *
 * The function cleans up all remaining resources, including the camera window and the graphics scene it uses.
 */
MainWindow::~MainWindow()
{
    delete graphicsScene;
    delete cw;
    delete ui;
}

/**
 * @brief Set a lock to prevent image updating
 *
 * The function enables or disables all buttons the modifiy the base image.
 * It is used to prevent unexpected behaviours when two set image operations are invoked simultaniously.
 *
 * @param lock @c true if the image should be locked, @c false if the image should be unlocked
 */
void MainWindow::setImageLock(bool lock)
{
    ui->actionCamera->setEnabled(!lock); // lock camera button
    ui->actionOpen->setEnabled(!lock); // lock open button
    ui->clearButton->setEnabled(!lock); // lock filter clear button
    if (lock || ui->effectList->currentRow() == -1) { // apply filter button, handle special case of no filter selected
        ui->applyButton->setEnabled(false);
    } else {
        ui->applyButton->setEnabled(true);
    }
}

void MainWindow::onActionUndoTriggered()
{
    graphicsScene->undo();
}

/**
 * @brief Handles the action when the user clicks the save button.
 *
 * The function pops up a dialog asking the saving location.
 * Then, the current screen image is saved to the location specified.
 */
void MainWindow::on_actionSave_triggered()
{
    QImage &&snapshot = graphicsScene->createSnapshot(); // captures the current screen
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image to File System", "untitled.png", "Images (*.png *.xpm *.jpg)"); // open save dialog
    snapshot.save(fileName); // save the image
}

/**
 * @brief Handles the action when the user clicks the camera button.
 *
 * The function opens the camera window.
 */
void MainWindow::on_actionCamera_triggered()
{
    if (cw) return; // ignore if a camera window is already opened
    setImageLock(true); // lock image buttons
    cw = new CameraWindow(this); // create a new camera window
    cw->show(); // show the window
    connect(cw, &CameraWindow::closed, this, &MainWindow::onCameraCaptured); // connect the close signal to the handler
}

/**
 * @brief Handles the action when the user clicks the enter button in the text tool.
 *
 * The function add the text typed by the user into the scene.
 */
void MainWindow::on_textEnterButton_clicked()
{
    QFont font = ui->fontComboBox->currentFont(); // get the font selected
    font.setPointSize(ui->spinBox->value()); // set the size of text
    QColor color = ui->textColor->getColor(); // get the color selected

    Sticker<QGraphicsTextItem> *textSticker =
            new Sticker<QGraphicsTextItem>(ui->textEdit->text()); // add the text item

    textSticker->setFont(font); // set the font
    textSticker->setDefaultTextColor(color); // set the text color

    graphicsScene->addSticker(textSticker); // add the text to scene
}


/**
 * @brief Handles the action when the user changes the value in text size slider.
 *
 * The function synchronize the text size slider with the text size spinner.
 *
 * @param x the value of the slider
 */
void MainWindow::on_horizontalSlider_valueChanged(int x)
{
    ui->spinBox->setValue(x);
}

/**
 * @brief Handles the action when the user changes the value in text size spinner.
 *
 * The function synchronize the text size spinner with the text size slider.
 *
 * @param x the value of the spinner
 */
void MainWindow::on_spinBox_valueChanged(int x)
{
    ui->horizontalSlider->setValue(x);
}

/**
 * @brief Handles the action when the user changes the value in pen size slider.
 *
 * The function sychronize the pen size slider with the pen size spinner.
 *
 * @param x the value of the slider
 */
void MainWindow::on_penSlider_valueChanged(int x)
{
    ui->penSpinner->setValue(x);
    graphicsScene->setStrokeWidth(x);
}

/**
 * @brief Handles the action when the user changes the value in pen size spinner.
 *
 * The function sychronize the pen size slider with the pen size spinner.
 *
 * @param x the value of the spinner
 */
void MainWindow::on_penSpinner_valueChanged(int x)
{
    ui->penSlider->setValue(x);
    graphicsScene->setStrokeWidth(x);
}

/**
 * @brief Handle the action when the user clicks on the open button.
 *
 * The function opens the file selection window allowing users to select the image file.
 * Then, the image is loaded into the graphics scene.
 */
void MainWindow::on_actionOpen_triggered()
{
    setImageLock(true); // lock the image reloated buttons
    QString fileName = QFileDialog::getOpenFileName(this, "Import Image from File System", QString(), "Images (*.png *.xpm *.jpg)"); // file dialog getting the filename
    QImage image{fileName}; // load image from file
    graphicsScene->setImage(image); // load image to scene
    setImageLock(false); // unlock the buttons
}

/**
 * @brief Handle the action when the user clicks on the share button.
 *
 * The function call the Imgur API to share the current scene image.
 */
void MainWindow::on_actionShare_triggered()
{
    imgur->shareImage(graphicsScene->createSnapshot()); // share the current scene image
}

/**
 * @brief Handle the action when the user changes the pen color selection.
 *
 * The function updates the pen color in the graphics scene.
 *
 * @param color the new pen color
 */
void MainWindow::on_penColor_colorChanged(QColor color)
{
    graphicsScene->setPenColor(color);
}

void MainWindow::on_actionDelete_triggered()
{
    graphicsScene->deleteSelected();
}

void MainWindow::on_actionToFront_triggered()
{
    graphicsScene->bringToFrontSelected();
}

void MainWindow::m_on_gps_selectionChanged()
{
    QList<QGraphicsItem *> selections = graphicsScene->selectedItems();
    if(selections.isEmpty())
        ui->stickerToolbar->hide();
    else
        ui->stickerToolbar->show();
}

void MainWindow::on_tabWidget_currentChanged(int tab)
{
    if(tab == TAB_PEN)
        graphicsScene->setMode(MyGraphicsScene::Mode::penMode);
    else if(tab == TAB_STICKER)
        graphicsScene->setMode(MyGraphicsScene::Mode::stickerMode);
}

void MainWindow::on_stickerTableView_clicked(const QModelIndex &index)
{
    graphicsScene->setStickerPath(index.data().toString());
}

void MainWindow::onCameraCaptured()
{
    graphicsScene->setImage(cw->result());
    cw->deleteLater();
    cw = nullptr;
    setImageLock(false);
}

void MainWindow::on_effectList_currentRowChanged(int row)
{
    if (row == -1) {
        ui->applyButton->setEnabled(false);
        return;
    }
    ui->applyButton->setEnabled(true);
    ImageFilter *effect = effectList[row];
    ui->effectSizeSlider->setEnabled(effect->sizeEnabled());
    ui->effectSizeSlider->setMaximum(effect->getMaxSize());
    ui->effectStrengthSlider->setEnabled(effect->strengthEnabled());
}

void MainWindow::on_applyButton_clicked()
{
    ImageFilter *filter = effectList[ui->effectList->currentRow()];
    int size = ui->effectSizeSlider->value();
    double strength = ui->effectStrengthSlider->value() / 1000.0;
    setImageLock(true);
    graphicsScene->applyEffect(filter, size, strength);
    setImageLock(false);
}

void MainWindow::on_clearButton_clicked()
{
    setImageLock(true);
    graphicsScene->clearEffect();
    setImageLock(false);
}

void MainWindow::onImageUploaded(QString imgId, QString imgLink)
{
    ExportDialog dialog(this, imgId, imgLink);
    dialog.exec();
}
