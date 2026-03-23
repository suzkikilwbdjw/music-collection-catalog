#include "add_artist_dialog.h"
#include "Dialogs/handler.h"
#include "Dialogs/validator.h"
#include "ui_add_artist_dialog.h"

#include <QMessageBox>
#include <QSqlRelationalDelegate>

AddArtistDialog::AddArtistDialog(Database *db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddArtistDialog)
    , _db(db)
{
    ui->setupUi(this);
    ui->careerActiveCheckBox->setText(tr("По настоящее время"));

    ui->popularSongComboBox->setModel(_db->getSongsModel());
    ui->countryComboBox->setModel(_db->getCountriesModel());

    ui->popularSongComboBox->setModelColumn(1);
    ui->countryComboBox->setModelColumn(1);

    ui->popularSongComboBox->insertItem(0, "Отсутствует", QVariant());
    ui->popularSongComboBox->setCurrentIndex(0);

    ui->dateOfBirthDateEdit->setCalendarPopup(true);
    ui->dateOfBirthDateEdit->setDisplayFormat("dd.MM.yyyy");
    ui->dateOfBirthDateEdit->setDate(QDate::currentDate());
    ui->dateOfBirthDateEdit->setMaximumDate(QDate::currentDate());
    ui->dateOfBirthDateEdit->setMinimumDate(QDate(1900, 1, 1));

    ui->careerEndDateEdit->setCalendarPopup(true);
    ui->careerEndDateEdit->setDisplayFormat("dd.MM.yyyy");
    ui->careerEndDateEdit->setDate(QDate::currentDate());
    ui->careerEndDateEdit->setMaximumDate(QDate::currentDate());
    ui->careerEndDateEdit->setMinimumDate(QDate(1900, 1, 1));

    ui->careerStartDateEdit->setCalendarPopup(true);
    ui->careerStartDateEdit->setDisplayFormat("dd.MM.yyyy");
    ui->careerStartDateEdit->setDate(QDate::currentDate());
    ui->careerStartDateEdit->setMaximumDate(QDate::currentDate());
    ui->careerStartDateEdit->setMinimumDate(QDate(1900, 1, 1));

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    QList<QLineEdit *> mandatoryFields = {ui->secondNameLineEdit,
                                          ui->firstNameLineEdit,
                                          ui->nicknameLineEdit};

    for (QLineEdit *field : mandatoryFields) {
        connect(field, &QLineEdit::textChanged, this, &AddArtistDialog::validateForm);
    }

    connect(ui->addCountryPushButton, &QPushButton::clicked, this, [&]() {
        Handler(_db, this).openAddCountryDialog(this);
    });

    connect(ui->addPopularSongPushButton, &QPushButton::clicked, this, [&]() {
        Handler(_db, this).openAddSongDialog(this);
    });

    connect(ui->careerActiveCheckBox, &QCheckBox::toggled, this, [this](bool checked) {
        ui->careerEndDateEdit->setEnabled(!checked);
    });

    validateForm();
}

AddArtistDialog::~AddArtistDialog()
{
    delete ui;
}
void AddArtistDialog::validateForm()
{
    bool isSecondNameOk = Validator::isValidString(ui->secondNameLineEdit->text());
    bool isFirstNameOk = Validator::isValidString(ui->firstNameLineEdit->text());
    bool isNicknameOk = Validator::isValidString(ui->nicknameLineEdit->text());
    bool isCountryOk = ui->countryComboBox->currentIndex() != -1;

    bool canAccept = isSecondNameOk && isFirstNameOk && isNicknameOk && isCountryOk;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canAccept);
}

void AddArtistDialog::on_buttonBox_accepted()
{
    try {
        QString careerEnd;
        if (!ui->careerActiveCheckBox->isChecked()) {
            careerEnd = ui->careerEndDateEdit->text();
        }

        QVariant popularSong;
        if (ui->popularSongComboBox->currentIndex() == 0) {
            popularSong = QVariant();
        } else {
            popularSong = ui->popularSongComboBox->currentText();
        }

        _db->getArtists()->add({{"second_name", ui->secondNameLineEdit->text()},
                                {"first_name", ui->firstNameLineEdit->text()},
                                {"patronymic", ui->patronymicLineEdit->text()},
                                {"nickname", ui->nicknameLineEdit->text()},
                                {"date_of_birth", ui->dateOfBirthDateEdit->text()},
                                {"career_start_date", ui->careerStartDateEdit->text()},
                                {"career_end_date", careerEnd},
                                {"popular_song_name", popularSong},
                                {"country_name", ui->countryComboBox->currentText()}});
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка: ", e.what());
    }
}
