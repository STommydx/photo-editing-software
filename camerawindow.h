#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QImage>
#include <QCameraImageCapture>

namespace Ui {
class CameraWindow;
}

class CameraWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CameraWindow(QWidget *parent = nullptr);
    ~CameraWindow() override;
    QImage result() const;

private:
    Ui::CameraWindow *ui;
    QCamera *cam;
    QCameraImageCapture *imgCap;
    QVector<int> captureList;
    QMap<int, QString> fileNameMap;
    QMap<int, int> captureMap;

protected:
    virtual void closeEvent(QCloseEvent *event) override;

signals:
    void closed();

private slots:
    void on_actionCapture_triggered();
    void on_actionFinishClose_triggered();
    void cameraImageCaptured(int id, const QImage &preview);
    void cameraImageSaved(int id, const QString &fileName);

};

#endif // CAMERAWINDOW_H
