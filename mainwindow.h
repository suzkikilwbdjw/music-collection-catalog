#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include "Database/database.h"
#include "Dialogs/handler.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupUI();
    void setupTable();

    void createArtistsTable();
    void createAlbumsTable();
    void createLabelsTable();
    void createCountriesTable();
    void createSongsTable();
    void createGenresTable();
public slots:
    void onClickedOpenFilePushButton();
    void onOpenDatabasePushButton();
    void onClickedAddPushButton();
    void onClickedRemovePushButton();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<Database> _db;
    std::unique_ptr<Handler> _handler;

    QString _filePathToDataBase;

    int getSelectedId(QTableView *view);
};
#endif // MAINWINDOW_H
