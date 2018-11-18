#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mygraphicsscene.h"

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

private slots:
    void on_actionTest_triggered();
    void on_actionSave_triggered();
    void on_textEnterButton_clicked();
};

#endif // MAINWINDOW_H
