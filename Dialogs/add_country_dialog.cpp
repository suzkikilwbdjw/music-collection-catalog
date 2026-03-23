#include "add_country_dialog.h"
#include <QMessageBox>
#include <QPushButton>
#include "Dialogs/validator.h"
#include "ui_add_country_dialog.h"
AddCountryDialog::AddCountryDialog(Database *db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddCountryDialog)
    , _db(db)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(ui->countryNameLineEdit, &QLineEdit::textChanged, this, [&](const QString &text) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(Validator::isValidString(text));
    });
}

AddCountryDialog::~AddCountryDialog()
{
    delete ui;
}

void AddCountryDialog::on_buttonBox_accepted()
{
    try {
        _db->getCountries()->add({
            {"country_name", ui->countryNameLineEdit->text()},
        });
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка: ", e.what());
    }
}
