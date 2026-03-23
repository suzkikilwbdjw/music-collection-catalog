#ifndef ADD_SONG_DIALOG_H
#define ADD_SONG_DIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include "Database/database.h"

namespace Ui {
class AddSongDialog;
}

class AddSongDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSongDialog(Database *db, QWidget *parent = nullptr);
    ~AddSongDialog();

private slots:
    void on_buttonBox_accepted();
    void validateForm();

private:
    Database *_db;
    Ui::AddSongDialog *ui;
};

#endif // ADD_SONG_DIALOG_H
