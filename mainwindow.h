#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mygraphicsscene.h"
#include "camerawindow.h"
#include "filtereffect.h"

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
    Ui::MainWindow *ui;
    MyGraphicsScene *gps;
    CameraWindow *cw;
    QVector<FilterEffect> effectList;

    void setupEffectList();

private slots:
    void on_actionTest_triggered();
    void on_actionSave_triggered();
    void on_actionCamera_triggered();
    void on_textEnterButton_clicked();
    void on_horizontalSlider_valueChanged(int x);
    void on_penSlider_valueChanged(int x);
    void on_spinBox_valueChanged(int x);
    void on_penSpinner_valueChanged(int x);
    void on_actionOpen_triggered();
    void onCameraCaptured();
    void on_effectList_currentRowChanged(int row);
    void on_applyButton_clicked();
    void on_clearButton_clicked();
};

#endif // MAINWINDOW_H
