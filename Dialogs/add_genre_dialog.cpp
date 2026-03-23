#include "add_genre_dialog.h"
#include <QMessageBox>
#include <QPushButton>
#include "Dialogs/validator.h"
#include "ui_add_genre_dialog.h"

AddGenreDialog::AddGenreDialog(Database *db, QWidget *parent)
    : QDialog(parent)
    , _db(db)
    , ui(new Ui::AddGenreDialog)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    connect(ui->genreNamelineEdit, &QLineEdit::textChanged, this, [&](const QString &text) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(Validator::isValidString(text));
    });
}

AddGenreDialog::~AddGenreDialog()
{
    delete ui;
}

void AddGenreDialog::on_buttonBox_accepted()
{
    try {
        _db->getGenres()->add({
            {"genre_name", ui->genreNamelineEdit->text()},
        });
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка: ", e.what());
    }
}
