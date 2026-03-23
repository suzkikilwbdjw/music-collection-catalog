#ifndef ADD_ARTIST_DIALOG_H
#define ADD_ARTIST_DIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include "Database/database.h"

namespace Ui {
class AddArtistDialog;
}

class AddArtistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddArtistDialog(Database *db, QWidget *parent = nullptr);
    ~AddArtistDialog();

private slots:
    void on_buttonBox_accepted();
    void validateForm();

private:
    Ui::AddArtistDialog *ui;
    Database *_db;
};

#endif // ADD_ARTIST_DIALOG_H
