#ifndef REMOVE_DIALOG_H
#define REMOVE_DIALOG_H

#include <QDialog>
#include "Database/database.h"
#include "table_type.h"

namespace Ui {
class RemoveDialog;
}

class RemoveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveDialog(Database *db, TableType tableType, int id, QWidget *parent = nullptr);
    ~RemoveDialog();
    void on_buttonBox_accepted();

private:
    Database *_db;
    TableType _tableType;
    int _id;
    Ui::RemoveDialog *ui;
};

#endif // REMOVE_DIALOG_H
