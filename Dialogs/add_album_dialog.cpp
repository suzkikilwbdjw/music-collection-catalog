#include "add_album_dialog.h"
#include <QMessageBox>
#include "Dialogs/handler.h"
#include "Dialogs/validator.h"
#include "ui_add_album_dialog.h"

AddAlbumDialog::AddAlbumDialog(Database *db, QWidget *parent)
    : QDialog(parent)
    , _db(db)
    , ui(new Ui::AddAlbumDialog)
{
    ui->setupUi(this);

    ui->labelComboBox->setModel(_db->getLabelsModel());
    ui->labelComboBox->setModelColumn(1);

    ui->labelComboBox->insertItem(0, "Отсутствует", QVariant());
    ui->labelComboBox->setCurrentIndex(0);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    ui->dateOfReleaseDateEdit->setCalendarPopup(true);
    ui->dateOfReleaseDateEdit->setDisplayFormat("dd.MM.yyyy");
    ui->dateOfReleaseDateEdit->setDate(QDate::currentDate());
    ui->dateOfReleaseDateEdit->setMaximumDate(QDate::currentDate());
    ui->dateOfReleaseDateEdit->setMinimumDate(QDate(1900, 1, 1));

    connect(ui->addLabelpushButton, &QPushButton::clicked, this, [&]() {
        Handler(_db, this).openAddLabelDialog(this);
    });

    connect(ui->albumNameLineEdit, &QLineEdit::textChanged, this, [&](const QString &text) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(Validator::isValidString(text));
    });
}

AddAlbumDialog::~AddAlbumDialog()
{
    delete ui;
}

void AddAlbumDialog::on_buttonBox_accepted()
{
    try {
        QVariant labelValue;

        if (ui->labelComboBox->currentIndex() == 0) {
            labelValue = QVariant();
        } else {
            labelValue = ui->labelComboBox->currentText();
        }

        _db->getAlbums()->add({
            {"label_name", labelValue},
            {"album_name", ui->albumNameLineEdit->text()},
            {"date_of_release", ui->dateOfReleaseDateEdit->text()},
        });
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}
