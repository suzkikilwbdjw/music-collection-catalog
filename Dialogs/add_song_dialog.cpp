#include "add_song_dialog.h"
#include <QMessageBox>
#include "Dialogs/handler.h"
#include "Dialogs/validator.h"
#include "ui_add_song_dialog.h"

AddSongDialog::AddSongDialog(Database *db, QWidget *parent)
    : QDialog(parent)
    , _db(db)
    , ui(new Ui::AddSongDialog)
{
    ui->setupUi(this);

    ui->artistComboBox->setModel(_db->getArtistsModel());
    ui->albumComboBox->setModel(_db->getAlbumsModel());
    ui->labelComboBox->setModel(_db->getLabelsModel());
    ui->genreComboBox->setModel(_db->getGenresModel());

    ui->artistComboBox->setModelColumn(4);
    ui->albumComboBox->setModelColumn(1);
    ui->labelComboBox->setModelColumn(1);
    ui->genreComboBox->setModelColumn(1);

    ui->albumComboBox->insertItem(0, "Отсутствует", QVariant());
    ui->albumComboBox->setCurrentIndex(0);
    ui->albumComboBox->update();

    ui->labelComboBox->insertItem(0, "Отсутствует", QVariant());
    ui->labelComboBox->setCurrentIndex(0);

    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDisplayFormat("dd.MM.yyyy");
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMaximumDate(QDate::currentDate());
    ui->dateEdit->setMinimumDate(QDate(1900, 1, 1));

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    QList<QLineEdit *> mandatoryFieldsString = {
        ui->songNameLineEdit,
        ui->textLineEdit,
        ui->ratingLineEdit,
        ui->durationLineEdit,
        ui->numberOfAuditionsLineEdit,
    };

    for (QLineEdit *field : mandatoryFieldsString) {
        connect(field, &QLineEdit::textChanged, this, &AddSongDialog::validateForm);
    }

    connect(ui->addArtistPushButton, &QPushButton::clicked, this, [&]() {
        Handler(_db, this).openAddArtistDialog(this);
    });
    connect(ui->addAlbumPushButton, &QPushButton::clicked, this, [&]() {
        Handler(_db, this).openAddAlbumDialog(this);
    });
    connect(ui->addLabelPushButton, &QPushButton::clicked, this, [&]() {
        Handler(_db, this).openAddLabelDialog(this);
    });
    connect(ui->addGenrePushButton, &QPushButton::clicked, this, [&]() {
        Handler(_db, this).openAddGenreDialog(this);
    });
}

void AddSongDialog::validateForm()
{
    bool isSongNameOk = Validator::isValidString(ui->songNameLineEdit->text());
    bool isTextOk = Validator::isValidString(ui->textLineEdit->text());
    bool isRatingOk = Validator::isValidNumberDouble(ui->ratingLineEdit->text());
    bool isDurationOK = Validator::isValidNumberInt(ui->durationLineEdit->text());
    bool isNumberOfAuditionsOk = Validator::isValidNumberInt(ui->numberOfAuditionsLineEdit->text());
    bool canAccept = isSongNameOk && isTextOk && isRatingOk && isNumberOfAuditionsOk
                     && isDurationOK;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(canAccept);
}
AddSongDialog::~AddSongDialog()
{
    delete ui;
}

void AddSongDialog::on_buttonBox_accepted()
{
    try {
        QVariant labelValue;

        if (ui->labelComboBox->currentIndex() == 0) {
            labelValue = QVariant();
        } else {
            labelValue = ui->labelComboBox->currentText();
        }

        QVariant albumValue;

        if (ui->albumComboBox->currentIndex() == 0) {
            albumValue = QVariant();
        } else {
            albumValue = ui->albumComboBox->currentText();
        }

        _db->getSongs()->add({
            {"song_name", ui->songNameLineEdit->text()},
            {"nickname", ui->artistComboBox->currentText()},
            {"date_of_create", ui->dateEdit->text()},
            {"duration", ui->durationLineEdit->text()},
            {"rating", ui->ratingLineEdit->text().toDouble()},
            {"text", ui->textLineEdit->text()},
            {"number_of_auditions", ui->numberOfAuditionsLineEdit->text().toInt()},
            {"album_name", albumValue},
            {"label_name", labelValue},
            {"genre_name", ui->genreComboBox->currentText()},
        });
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка: ", e.what());
    }
}
