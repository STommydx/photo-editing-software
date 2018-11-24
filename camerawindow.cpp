#include <QCameraInfo>
#include <QMessageBox>
#include <QDebug>
#include <QListWidgetItem>

#include "camerawindow.h"
#include "ui_camerawindow.h"

CameraWindow::CameraWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CameraWindow),
    cam(nullptr),
    imgCap(nullptr)
{
    ui->setupUi(this);
    ui->listWidget->setViewMode(QListWidget::IconMode);
    ui->listWidget->setResizeMode(QListWidget::Adjust);
    ui->listWidget->setIconSize(QSize(150, 150));

    QList<QCameraInfo> camInfo = QCameraInfo::availableCameras();
    if (camInfo.size() > 0) {
        cam = new QCamera(camInfo[0]);
        cam->setViewfinder(ui->cameraViewfinder);
        cam->start();
        imgCap = new QCameraImageCapture(cam);
        connect(imgCap, &QCameraImageCapture::imageCaptured, this, &CameraWindow::cameraImageCaptured);
        connect(imgCap, &QCameraImageCapture::imageSaved, this, &CameraWindow::cameraImageSaved);
    } else {
        QMessageBox::warning(this, "No Camera", "No camera found!!!");
    }
}

CameraWindow::~CameraWindow()
{
    delete ui;
    if (cam) cam->stop();
    delete cam;
    delete imgCap;
}

QImage CameraWindow::result() const
{
    if (captureList.empty()) return QImage();
    int idx = ui->listWidget->currentRow();
    if (idx == -1) idx = ui->listWidget->count() - 1;
    return QImage(fileNameMap[captureList[idx]]);
}

void CameraWindow::closeEvent(QCloseEvent *)
{
    emit closed();
}

void CameraWindow::on_actionCapture_triggered()
{
    cam->searchAndLock();
    imgCap->capture();
    cam->unlock();
}

void CameraWindow::on_actionFinishClose_triggered()
{
    if (captureList.empty()) {
        QMessageBox::warning(this, "Camera Capture", "Please capture at least one image to proceed.");
    } else {
        close();
    }
}

void CameraWindow::cameraImageCaptured(int id, const QImage &preview)
{
    captureMap[id] = captureList.count();
    captureList.push_back(id);
    ui->listWidget->addItem(new QListWidgetItem(QIcon(QPixmap::fromImage(preview)), "Capture " + QString::number(id)));
}

void CameraWindow::cameraImageSaved(int id, const QString &fileName)
{
    fileNameMap[id] = fileName;
    ui->listWidget->item(captureMap[id])->setToolTip(fileName);
}
