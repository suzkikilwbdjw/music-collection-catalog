#ifndef ADD_ALBUM_DIALOG_H
#define ADD_ALBUM_DIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include "Database/database.h"

namespace Ui {
class AddAlbumDialog;
}
class AddAlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAlbumDialog(Database *db, QWidget *parent = nullptr);
    ~AddAlbumDialog();
private slots:
    void on_buttonBox_accepted();

private:
    Database *_db;
    Ui::AddAlbumDialog *ui;
};

#endif // ADD_ALBUM_DIALOG_H
