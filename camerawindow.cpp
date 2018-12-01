/**
 * @class CameraWindow
 * @brief The CameraWindow class provides a simple interface for camera capturing.
 *
 *
 */

#include <QCameraInfo>
#include <QMessageBox>
#include <QDebug>
#include <QListWidgetItem>

#include "camerawindow.h"
#include "ui_camerawindow.h"

/**
 * @brief Constructs a new window for camera capturing.
 *
 * The constructor does all the necessary setup to initailize the camera.
 * It also setup the UI for viewing the camera.
 *
 * @param parent the parent widget
 */
CameraWindow::CameraWindow(QWidget *parent) :
    QMainWindow(parent), // invoke parent constructor
    ui(new Ui::CameraWindow), // instantiate UI
    cam(nullptr), // initialize QCamera
    imgCap(nullptr) // initialize QCameraImageCapture
{
    ui->setupUi(this); // setup UI
    ui->listWidget->setViewMode(QListWidget::IconMode); // set list to display captured pictures
    ui->listWidget->setResizeMode(QListWidget::Adjust); // set list to adjust while resizing
    ui->listWidget->setIconSize(QSize(150, 150)); // set icon size

    QList<QCameraInfo> camInfo = QCameraInfo::availableCameras(); // get availiable cameras
    if (camInfo.size() > 0) { // if there is a camera availiable
        cam = new QCamera(camInfo[0]); // get the first one
        cam->setViewfinder(ui->cameraViewfinder); // connect camera to ui
        cam->start(); // start the camera
        imgCap = new QCameraImageCapture(cam); // instantiate capture device
        connect(imgCap, &QCameraImageCapture::imageCaptured, this, &CameraWindow::cameraImageCaptured); // connect handler for image capture
        connect(imgCap, &QCameraImageCapture::imageSaved, this, &CameraWindow::cameraImageSaved); // connect hanfler for image save
    } else {
        QMessageBox::warning(this, "No Camera", "No camera found!!!"); // warn the user if there is no cammera
    }
}

/**
 * @brief Destructs the camera window
 */
CameraWindow::~CameraWindow()
{
    delete ui; // delete the ui
    if (cam) cam->stop(); // stop the camera
    delete cam; // delete the memory used by camera
    delete imgCap; // delete the capture device
}

/**
 * @brief Return the selected capture image in the selection list
 *
 * The function will return the image selected if there is any.
 * Otherwise, it will return the last image captured.
 * Note that a null image will be returned if there is no captures.
 *
 * @return the selected capture image
 */
QImage CameraWindow::result() const
{
    if (captureList.empty()) return QImage(); // return null image if there is nothing got captured
    int idx = ui->listWidget->currentRow(); // set the select index to current row
    if (idx == -1) idx = ui->listWidget->count() - 1; // if there is not a item that get selected, set the select index to last item
    return QImage(fileNameMap[captureList[idx]]); // return the image for the index selected
}

/**
 * @brief Handles the action when the application is closed
 *
 * The function will emit CameraWindow::closed() signal.
 */
void CameraWindow::closeEvent(QCloseEvent *)
{
    emit closed(); // emit closed signal when the window is closed
}

/**
 * @brief Handles the action when the user clicks on the capture button
 *
 * The function will lock the camera tempoarily and capture an image.
 */
void CameraWindow::on_actionCapture_triggered()
{
    cam->searchAndLock(); // lock the camera before capture
    imgCap->capture(); // capture the image
    cam->unlock(); // unlock the camera after capture
}

/**
 * @brief Handles the action when the user clicks on the finish and close button
 *
 * The function closes the capture window if there is at least one image captured.
 * Otherwise, it displays a warning to the user.
 */
void CameraWindow::on_actionFinishClose_triggered()
{
    if (captureList.empty()) { // check if there is an image captured before proceeeding
        QMessageBox::warning(this, "Camera Capture", "Please capture at least one image to proceed.");
    } else {
        close(); // can safely close as there is at least one image captured
    }
}

/**
 * @brief Handles the action when an camera image has been captured
 *
 * The function registers the capture to the capture list widget which display the image to the user.
 * It also stores the capture information in the respective lists and maps.
 *
 * @param id the capture id
 * @param preview the preview of the image
 */
void CameraWindow::cameraImageCaptured(int id, const QImage &preview)
{
    captureMap[id] = captureList.count(); // map the capture id to the selection list
    captureList.push_back(id); // add the image captured to the list
    ui->listWidget->addItem(new QListWidgetItem(QIcon(QPixmap::fromImage(preview)), "Capture " + QString::number(id))); // set the preview image
}

/**
 * @brief Handles the action when an camera image has been saved in the disk
 *
 * The function sets the tooltip of the respective photo in the capture list widget.
 * It also stores the file name into a map for CameraWindow::result().
 *
 * @param id the capture id
 * @param fileName the file name of the image
 */
void CameraWindow::cameraImageSaved(int id, const QString &fileName)
{
    fileNameMap[id] = fileName; // map the capture id to file name
    ui->listWidget->item(captureMap[id])->setToolTip(fileName); // set the tooltip of the image to be the file name
}

/**
 * @fn CameraWindow::closed()
 * @brief The signal emitted when the window is closed.
 */
