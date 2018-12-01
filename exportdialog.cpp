/**
 * @class ExportDialog
 * @brief The ExportDialog class provides a dialog for displaying the export result.
 *
 * The dialog display links of the image.
 * There are additional buttons that user can click on for copying the links to the system clopboard.
 */

#include <QClipboard>

#include "exportdialog.h"
#include "ui_exportdialog.h"

/**
 * @brief Constructs an ExportDoalog with the given id and link.
 * @param parent the parent widget
 * @param imgId the image id
 * @param imgLink the image link
 */
ExportDialog::ExportDialog(QWidget *parent, const QString &imgId, const QString &imgLink) :
    QDialog(parent), // call parent constructor
    ui(new Ui::ExportDialog) // instantiate the ui
{
    ui->setupUi(this); // setup the ui
    ui->idEdit->setText(imgId); // set the id field
    ui->linkEdit->setText(imgLink); // set the image link field
    ui->shareEdit->setText("https://imgur.com/" + imgId); // set the share link field using imgur url and id
}

/**
 * @brief Destruct the ExportDialog.
 */
ExportDialog::~ExportDialog()
{
    delete ui;
}

/**
 * @brief Handles the action when the user clicks the copy button near image id.
 *
 * Copys the image ID to the system clipboard.
 */
void ExportDialog::on_idButton_clicked()
{
    QApplication::clipboard()->setText(ui->idEdit->text());
}

/**
 * @brief Handles the action when the user clicks the copy button near link.
 *
 * Copys the link to the system clipboard.
 */
void ExportDialog::on_linkButton_clicked()
{
    QApplication::clipboard()->setText(ui->linkEdit->text());
}

/**
 * @brief Handles the action when the user clicks the copy button near share link.
 *
 * Copys the share link to the system clipboard.
 */
void ExportDialog::on_shareButton_clicked()
{
    QApplication::clipboard()->setText(ui->shareEdit->text());
}
