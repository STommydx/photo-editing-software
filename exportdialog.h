#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = nullptr, const QString &imgId = QString(), const QString &imgLink = QString());
    ~ExportDialog();

private:
    Ui::ExportDialog *ui;

private slots:
    void on_idButton_clicked();
    void on_linkButton_clicked();
    void on_shareButton_clicked();

};

#endif // EXPORTDIALOG_H
