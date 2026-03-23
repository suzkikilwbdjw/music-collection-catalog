#ifndef ADD_COUNTRY_DIALOG_H
#define ADD_COUNTRY_DIALOG_H

#include <QDialog>
#include "Database/database.h"

namespace Ui {
class AddCountryDialog;
}

class AddCountryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCountryDialog(Database *db, QWidget *parent = nullptr);
    ~AddCountryDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddCountryDialog *ui;
    Database *_db;
};

#endif // ADD_COUNTRY_DIALOG_H
