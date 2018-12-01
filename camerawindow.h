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
    Ui::CameraWindow *ui; /**< @brief The CameraWindow UI. */
    QCamera *cam; /**< @brief Pointer to the capture camera. */
    QCameraImageCapture *imgCap; /**< @brief Pointer to image capture device. */
    QVector<int> captureList; /**< @brief The list of capture ids */
    QMap<int, QString> fileNameMap; /**< @brief A map that maps between capture id and file name */
    QMap<int, int> captureMap; /**< @brief A map that maps between capture id and selection list */

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
