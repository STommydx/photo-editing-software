#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mygraphicsscene.h"
#include "stickerthumbnailsmodel.h"
#include "stickerthumbnailsdelegate.h"
#include "camerawindow.h"
#include "imgurwrapper.h"
#include "filter/defaultfilterlist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    static const int TAB_PEN = 0;
    static const int TAB_STICKER = 1;
    Ui::MainWindow *ui;
    MyGraphicsScene *graphicsScene;
    StickerThumbnailsModel* model;
    StickerThumbnailsDelegate* delegate;
    CameraWindow *cw;
    DefaultFilterList effectList;
    ImgurWrapper *imgur;
    void setImageLock(bool lock);

private slots:
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionShare_triggered();

    // Sticker toolbars
    void onActionUndoTriggered();
    void m_on_gps_selectionChanged();
    void on_actionDelete_triggered();
    void on_actionToFront_triggered();

    // Sticker build options
    void on_stickerTableView_clicked(const QModelIndex &index);
    void on_tabWidget_currentChanged(int tab);
    void on_penColor_colorChanged(QColor color);
    void on_textEnterButton_clicked();
    void on_horizontalSlider_valueChanged(int x);
    void on_penSlider_valueChanged(int x);
    void on_spinBox_valueChanged(int x);
    void on_penSpinner_valueChanged(int x);

    // Camera
    void onCameraCaptured();
    void on_actionCamera_triggered();

    void on_effectList_currentRowChanged(int row);
    void on_applyButton_clicked();
    void on_clearButton_clicked();

    void onImageUploaded(QString imgId, QString imgLink);
};

#endif // MAINWINDOW_H
