#include <QClipboard>

#include "exportdialog.h"
#include "ui_exportdialog.h"

ExportDialog::ExportDialog(QWidget *parent, const QString &imgId, const QString &imgLink) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);
    ui->idEdit->setText(imgId);
    ui->linkEdit->setText(imgLink);
    ui->shareEdit->setText("https://imgur.com/" + imgId);
}

ExportDialog::~ExportDialog()
{
    delete ui;
}

void ExportDialog::on_idButton_clicked()
{
    QApplication::clipboard()->setText(ui->idEdit->text());
}

void ExportDialog::on_linkButton_clicked()
{
    QApplication::clipboard()->setText(ui->linkEdit->text());
}

void ExportDialog::on_shareButton_clicked()
{
    QApplication::clipboard()->setText(ui->shareEdit->text());
}
