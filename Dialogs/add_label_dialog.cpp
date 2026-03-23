#include "add_label_dialog.h"
#include <QMessageBox>
#include <QPushButton>
#include "Dialogs/handler.h"
#include "Dialogs/validator.h"
#include "ui_add_label_dialog.h"

AddLabelDialog::AddLabelDialog(Database *db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddLabelDialog)
    , _db(db)
{
    ui->setupUi(this);

    ui->countryComboBox->setModel(_db->getCountriesModel());
    ui->countryComboBox->setModelColumn(1);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    connect(ui->labelNameLineEdit, &QLineEdit::textChanged, this, [&](const QString &text) {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(Validator::isValidString(text));
    });

    connect(ui->addCountryPushButton, &QPushButton::clicked, this, [&]() {
        Handler(_db, this).openAddCountryDialog(this);
    });
}

AddLabelDialog::~AddLabelDialog()
{
    delete ui;
}

void AddLabelDialog::on_buttonBox_accepted()
{
    try {
        _db->getLabels()->add({
            {"country_name", ui->countryComboBox->currentText()},
            {"label_name", ui->labelNameLineEdit->text()},
        });
        accept();
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка: ", e.what());
    }
}

void AddLabelDialog::on_buttonBox_rejected()
{
    reject();
}
