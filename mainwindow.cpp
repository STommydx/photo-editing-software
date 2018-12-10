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
#include <QPixmap>
#include <QBitmap>

#include "editorgraphicsscene.h"
#include "utils/imageutil.h"
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
    graphicsScene(new EditorGraphicsScene), // instantiate graphics scene for viewing
    model(new StickerThumbnailsModel(this)),
    delegate(new StickerThumbnailsDelegate(this)),
    cameraWindow(nullptr), // initialize camera window pointer
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

    connect(graphicsScene, &EditorGraphicsScene::selectionChanged, this, &MainWindow::onSceneSelectionChanged); // handle selection change
    connect(imgur, &ImgurWrapper::imageUploaded, this, &MainWindow::onImageUploaded); // handle image upload signal

    // hack fixes for icon colors
    auto hackfix = [&](QAction *action, QString file) {
        QPixmap icon(file);
        QBitmap iconMask = icon.createMaskFromColor(Qt::transparent);
        icon.fill(ui->mainToolBar->palette().toolTipText().color());
        icon.setMask(iconMask);
        action->setIcon(QIcon{icon});
    };
    hackfix(ui->actionCamera, ":/toolbar/camera.png");
    hackfix(ui->actionDelete, ":/toolbar/delete.png");
    hackfix(ui->actionOpen, ":/toolbar/open.png");
    hackfix(ui->actionSave, ":/toolbar/save.png");
    hackfix(ui->actionShare, ":/toolbar/share.png");
    hackfix(ui->actionToFront, ":/toolbar/front.png");

}

/**
 * @brief Destructs the main window.
 *
 * The function cleans up all remaining resources, including the camera window and the graphics scene it uses.
 */
MainWindow::~MainWindow()
{
    delete graphicsScene;
    delete cameraWindow;
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
    if (cameraWindow) return; // ignore if a camera window is already opened
    setImageLock(true); // lock image buttons
    cameraWindow = new CameraWindow(this); // create a new camera window
    cameraWindow->show(); // show the window
    connect(cameraWindow, &CameraWindow::closed, this, &MainWindow::onCameraCaptured); // connect the close signal to the handler
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
 * @brief Handles the action when the user clicks on the share button.
 *
 * The function call the Imgur API to share the current scene image.
 */
void MainWindow::on_actionShare_triggered()
{
    imgur->shareImage(graphicsScene->createSnapshot()); // share the current scene image
}

/**
 * @brief Handles the action when the user changes the pen color selection.
 *
 * The function updates the pen color in the graphics scene.
 *
 * @param color the new pen color
 */
void MainWindow::on_penColor_colorChanged(QColor color)
{
    graphicsScene->setPenColor(color);
}

/**
 * @brief Handles the action when the user clicks on the delete button.
 *
 * The function deletes the current selected sticker.
 */
void MainWindow::on_actionDelete_triggered()
{
    graphicsScene->deleteSelected();
}

/**
 * @brief Handles the action when the user clicks the to front button.
 *
 * The function brings the selected sticker to the front of the scene.
 */
void MainWindow::on_actionToFront_triggered()
{
    graphicsScene->bringToFrontSelected();
}

/**
 * @brief Handles the action when the user selects a different sticker
 *
 * The function shows or hides the sticker toolbar according whether there exist a sticker selection.
 */
void MainWindow::onSceneSelectionChanged()
{
    QList<QGraphicsItem *> &&selections = graphicsScene->selectedItems();
    if(selections.isEmpty()) // if nothing is selected
        ui->stickerToolbar->hide();
    else
        ui->stickerToolbar->show();
}

/**
 * @brief Handles the action when the user selects a differenet tab.
 *
 * The function set the respective mode of the graphic scene.
 *
 * @param tab the new tab index
 */
void MainWindow::on_tabWidget_currentChanged(int tab)
{
    if(tab == TAB_PEN)
        graphicsScene->setMode(EditorGraphicsScene::Mode::penMode);
    else if(tab == TAB_STICKER)
        graphicsScene->setMode(EditorGraphicsScene::Mode::stickerMode);
    else if(tab == TAB_EFFECT)
        graphicsScene->setMode(EditorGraphicsScene::Mode::effectMode);
}

/**
 * @brief Handles the action when the user clicks on a different sticker in the sticker selection tab
 *
 * Updates the sticker file path of graphics scene.
 *
 * @param index the new selection index
 */
void MainWindow::on_stickerTableView_clicked(const QModelIndex &index)
{
    graphicsScene->setStickerPath(index.data().toString());
}

/**
 * @brief Handles the action when an image has been selected from the camera capture window.
 *
 * The function is invoked when the camera window is closed.
 * It sets the result image to the graphics scene.
 * Also, it cleans up the resources used by the camera window.
 */
void MainWindow::onCameraCaptured()
{
    graphicsScene->setImage(cameraWindow->result()); // set the result image to scene
    cameraWindow->deleteLater(); // schedule for deletion
    cameraWindow = nullptr; // no dangling pointer!
    setImageLock(false); // unlock the image related buttons
}

/**
 * @brief Handles the action when the a different effect is being selected.
 *
 * The function updates the apply button, effect size slider and the effect strength slider according to the settings of the filter.
 *
 * @param row the selected row in effect list
 */
void MainWindow::on_effectList_currentRowChanged(int row)
{
    if (row == -1) { // if nothing is selected
        ui->applyButton->setEnabled(false); // disable apply button
        return;
    }
    ui->applyButton->setEnabled(true);
    ImageFilter *effect = effectList[row];
    ui->effectSizeSlider->setEnabled(effect->sizeEnabled()); // enable size slider according to settings
    ui->effectSizeSlider->setMaximum(effect->getMaxSize()); // set max size according to settings
    ui->effectStrengthSlider->setEnabled(effect->strengthEnabled()); // enable strength slider according to settings
}

/**
 * @brief Handles the action when the apply button is clicked.
 *
 * Apply the selected filter effect to the image.
 */
void MainWindow::on_applyButton_clicked()
{
    ImageFilter *filter = effectList[ui->effectList->currentRow()]; // get the current filter
    int size = ui->effectSizeSlider->value();
    double strength = ui->effectStrengthSlider->value() / 1000.0; // normalize the strength slider value
    setImageLock(true); // lock buttons before applying
    graphicsScene->applyEffect(filter, size, strength); // apply the effects
    setImageLock(false); // unlock the buttons
}

/**
 * @brief Handles the action when the clear button is clicked.
 *
 * Clear all the effect applied.
 */
void MainWindow::on_clearButton_clicked()
{
    setImageLock(true); // lock the buttons before clearing
    graphicsScene->clearEffect(); // clear the effects
    setImageLock(false); // unlock the buttons
}

/**
 * @brief Handles the action when an image has been successfully uploaded to Imgur.
 *
 * Construct a corresponding upload finish dialog and display it to the user.
 *
 * @param imgId the image id
 * @param imgLink the image link
 */
void MainWindow::onImageUploaded(QString imgId, QString imgLink)
{
    ExportDialog dialog(this, imgId, imgLink);
    dialog.exec();
}
