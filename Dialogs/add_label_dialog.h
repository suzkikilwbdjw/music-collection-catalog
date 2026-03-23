#ifndef ADD_LABEL_DIALOG_H
#define ADD_LABEL_DIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include "Database/database.h"

namespace Ui {
class AddLabelDialog;
}

class AddLabelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddLabelDialog(Database *db, QWidget *parent = nullptr);
    ~AddLabelDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddLabelDialog *ui;
    Database *_db;
};

#endif // ADD_LABEL_DIALOG_H
