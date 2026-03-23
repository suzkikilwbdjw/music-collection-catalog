#ifndef ADD_GENRE_DIALOG_H
#define ADD_GENRE_DIALOG_H

#include <QDialog>
#include "Database/database.h"

namespace Ui {
class AddGenreDialog;
}

class AddGenreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddGenreDialog(Database *db, QWidget *parent = nullptr);
    ~AddGenreDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Database *_db;
    Ui::AddGenreDialog *ui;
};

#endif // ADD_GENRE_DIALOG_H
