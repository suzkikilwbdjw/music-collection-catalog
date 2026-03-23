#include "mainwindow.h"
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlError>
#include <QSqlRelationalDelegate>
#include <QTableWidget>

#include "Delegates/album_delegate.h"
#include "Delegates/artist_delegate.h"
#include "Delegates/country_delegate.h"
#include "Delegates/genre_delegate.h"
#include "Delegates/song_delegate.h"

#include "Dialogs/remove_dialog.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();

    connect(ui->openFilePushButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onClickedOpenFilePushButton);

    connect(ui->openDatabasePushButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onOpenDatabasePushButton);
    connect(ui->addPushButton, &QPushButton::clicked, this, &MainWindow::onClickedAddPushButton);

    connect(ui->removePushButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onClickedRemovePushButton);

    ui->openFilePushButton->setDefault(true);
}
void MainWindow::setupUI()
{
    ui->filePathlineEdit->setReadOnly(true);
    ui->openDatabasePushButton->setEnabled(false);
    ui->addPushButton->setEnabled(false);
    ui->removePushButton->setEnabled(false);
    ui->tabWidget->setTabText(0, tr("Исполнители"));
    ui->tabWidget->setTabText(1, tr("Страны"));
    ui->tabWidget->setTabText(2, tr("Лейблы"));
    ui->tabWidget->setTabText(3, tr("Альбомы"));
    ui->tabWidget->setTabText(4, tr("Песни"));
    ui->tabWidget->setTabText(5, tr("Жанры"));
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::setupTable()
{
    createArtistsTable();
    createAlbumsTable();
    createLabelsTable();
    createSongsTable();
    createGenresTable();
    createCountriesTable();
}

void MainWindow::createArtistsTable()
{
    QSqlRelationalTableModel *artistsModel = _db->getArtistsModel();

    _db->getArtistsModel()->setEditStrategy(QSqlTableModel::OnFieldChange);
    artistsModel->setTable("Artists");

    ui->artistsTableView->setModel(artistsModel);

    artistsModel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    artistsModel->setRelation(8, QSqlRelation("Songs", "id", "name"));
    artistsModel->setRelation(9, QSqlRelation("Countries", "id", "name"));

    ui->artistsTableView->setItemDelegate(new ArtistDelegate(ui->artistsTableView));

    if (!artistsModel->select())
        QMessageBox::critical(this,
                              "Ошибка чтения таблицы Артисты",
                              artistsModel->lastError().text());

    artistsModel->setHeaderData(0, Qt::Horizontal, tr("id"));
    artistsModel->setHeaderData(1, Qt::Horizontal, tr("Фамилия"));
    artistsModel->setHeaderData(2, Qt::Horizontal, tr("Имя"));
    artistsModel->setHeaderData(3, Qt::Horizontal, tr("Отчество"));
    artistsModel->setHeaderData(4, Qt::Horizontal, tr("Псевдоним"));
    artistsModel->setHeaderData(5, Qt::Horizontal, tr("Дата рождения"));
    artistsModel->setHeaderData(6, Qt::Horizontal, tr("Начало карьеры"));
    artistsModel->setHeaderData(7, Qt::Horizontal, tr("Конец карьеры"));
    artistsModel->setHeaderData(8, Qt::Horizontal, tr("Самая популярная песня"));
    artistsModel->setHeaderData(9, Qt::Horizontal, tr("Страна"));

    ui->artistsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(artistsModel, &QSqlTableModel::dataChanged, this, [=]() {
        _db->getSongsModel()->relationModel(2)->select();
        _db->getSongsModel()->select();
    });
}

void MainWindow::createAlbumsTable()
{
    QSqlRelationalTableModel *albumsModel = _db->getAlbumsModel();

    albumsModel->setTable("Albums");
    ui->albumsTableView->setModel(albumsModel);

    albumsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    albumsModel->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    albumsModel->setRelation(3, QSqlRelation("Labels", "id", "name"));

    ui->albumsTableView->setItemDelegate(new AlbumDelegate(ui->albumsTableView));

    if (!albumsModel->select())
        QMessageBox::critical(this,
                              "Ошибка чтения таблицы Альбомы",
                              albumsModel->lastError().text());

    albumsModel->setHeaderData(0, Qt::Horizontal, tr("id"));
    albumsModel->setHeaderData(1, Qt::Horizontal, tr("Название"));
    albumsModel->setHeaderData(2, Qt::Horizontal, tr("Дата выпуска"));
    albumsModel->setHeaderData(3, Qt::Horizontal, tr("Лейбл"));

    ui->albumsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(albumsModel, &QSqlTableModel::dataChanged, this, [=]() {
        _db->getSongsModel()->relationModel(8)->select();
        _db->getSongsModel()->select();
    });
}

void MainWindow::createLabelsTable()
{
    QSqlRelationalTableModel *labelsModel = _db->getLabelsModel();

    labelsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    labelsModel->setTable("Labels");
    ui->labelsTableView->setModel(labelsModel);

    labelsModel->setRelation(2, QSqlRelation("Countries", "id", "name"));
    ui->labelsTableView->setItemDelegate(new QSqlRelationalDelegate(ui->labelsTableView));

    if (!labelsModel->select())
        QMessageBox::critical(this, "Ошибка чтения таблицы Лейблы", labelsModel->lastError().text());

    labelsModel->setHeaderData(0, Qt::Horizontal, tr("id"));
    labelsModel->setHeaderData(1, Qt::Horizontal, tr("Названиe"));
    labelsModel->setHeaderData(2, Qt::Horizontal, tr("Страна"));

    ui->labelsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(labelsModel, &QSqlTableModel::dataChanged, this, [=]() {
        _db->getSongsModel()->relationModel(9)->select();
        _db->getSongsModel()->select();
    });

    connect(labelsModel, &QSqlTableModel::dataChanged, this, [=]() {
        _db->getAlbumsModel()->relationModel(3)->select();
        _db->getAlbumsModel()->select();
    });
}

void MainWindow::createSongsTable()
{
    QSqlRelationalTableModel *songsModel = _db->getSongsModel();
    songsModel->setObjectName("songsModel");
    songsModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    songsModel->setTable("Songs");
    ui->songsTableView->setModel(songsModel);

    songsModel->setRelation(2, QSqlRelation("Artists", "id", "nickname"));
    songsModel->setRelation(10, QSqlRelation("Genres", "id", "name"));

    songsModel->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    songsModel->setRelation(8, QSqlRelation("Albums", "id", "name"));
    songsModel->setRelation(9, QSqlRelation("Labels", "id", "name"));

    ui->songsTableView->setItemDelegate(new SongDelegate(ui->songsTableView));
    //ui->songsTableView->setItemDelegateForColumn(3, new DateDelegate(ui->songsTableView));

    if (!songsModel->select())
        QMessageBox::critical(this, "Ошибка чтения таблицы Песни", songsModel->lastError().text());

    songsModel->setHeaderData(0, Qt::Horizontal, tr("id"));
    songsModel->setHeaderData(1, Qt::Horizontal, tr("Название"));
    songsModel->setHeaderData(2, Qt::Horizontal, tr("Исполнитель"));
    songsModel->setHeaderData(3, Qt::Horizontal, tr("Дата выпуска"));
    songsModel->setHeaderData(4, Qt::Horizontal, tr("Длительность (сек.)"));
    songsModel->setHeaderData(5, Qt::Horizontal, tr("Рейтинг"));
    songsModel->setHeaderData(6, Qt::Horizontal, tr("Текст"));
    songsModel->setHeaderData(7, Qt::Horizontal, tr("Количество прослушиваний"));
    songsModel->setHeaderData(8, Qt::Horizontal, tr("Альбом"));
    songsModel->setHeaderData(9, Qt::Horizontal, tr("Лейбл"));
    songsModel->setHeaderData(10, Qt::Horizontal, tr("Жанр"));

    ui->songsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(songsModel, &QSqlTableModel::dataChanged, this, [=]() {
        _db->getArtistsModel()->relationModel(8)->select();
        _db->getArtistsModel()->select();
    });
}

void MainWindow::createCountriesTable()
{
    QSqlRelationalTableModel *countriesModel = _db->getCountriesModel();

    countriesModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    countriesModel->setTable("Countries");

    if (!countriesModel->select())
        QMessageBox::critical(this,
                              "Ошибка чтения таблицы Страны",
                              countriesModel->lastError().text());

    countriesModel->setHeaderData(0, Qt::Horizontal, tr("id"));
    countriesModel->setHeaderData(1, Qt::Horizontal, tr("Названиe"));

    ui->countriesTableView->setModel(countriesModel);
    ui->countriesTableView->setItemDelegate(new CountryDelegate(ui->countriesTableView));
    ui->countriesTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(countriesModel, &QSqlTableModel::dataChanged, this, [=]() {
        _db->getArtistsModel()->relationModel(9)->select();
        _db->getArtistsModel()->select();
    });

    connect(countriesModel, &QSqlTableModel::dataChanged, this, [=]() {
        _db->getLabelsModel()->relationModel(2)->select();
        _db->getLabelsModel()->select();
    });
}

void MainWindow::createGenresTable()
{
    QSqlRelationalTableModel *genresModel = _db->getGenresModel();
    genresModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    genresModel->setTable("Genres");

    ui->genresTableView->setModel(genresModel);
    ui->genresTableView->setItemDelegate(new GenreDelegate(ui->genresTableView));

    if (!genresModel->select())
        QMessageBox::critical(this, "Ошибка чтения таблицы Жанры", genresModel->lastError().text());

    genresModel->setHeaderData(0, Qt::Horizontal, tr("id"));
    genresModel->setHeaderData(1, Qt::Horizontal, tr("Названиe"));

    ui->genresTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(genresModel, &QSqlTableModel::dataChanged, this, [=]() {
        _db->getSongsModel()->relationModel(10)->select();
        _db->getSongsModel()->select();
    });
}
void MainWindow::onClickedOpenFilePushButton()
{
    ui->openDatabasePushButton->setEnabled(false);

    _filePathToDataBase
        = QFileDialog::getOpenFileName(this,
                                       tr("Open Database"),
                                       "/home/suzuki/Work/begynov/MusicCollectionCatalog",
                                       tr("Databases (*.db *.sqlite)"));
    if (!_filePathToDataBase.isEmpty()) {
        ui->filePathlineEdit->setText(_filePathToDataBase);
        ui->openDatabasePushButton->setDefault(true);
        ui->openDatabasePushButton->setEnabled(true);
        ui->openFilePushButton->setDefault(false);
    }
}

void MainWindow::onOpenDatabasePushButton()
{
    _db = std::make_unique<Database>(_filePathToDataBase);
    _handler = std::make_unique<Handler>(_db.get());
    ui->tabWidget->show();
    ui->addPushButton->setEnabled(true);
    ui->removePushButton->setEnabled(true);
    ui->addPushButton->setDefault(true);
    ui->openDatabasePushButton->setDefault(false);
    setupTable();
}

void MainWindow::onClickedAddPushButton()
{
    switch (ui->tabWidget->currentIndex()) {
    case 0:
        _handler->openAddArtistDialog(this);
        break;
    case 1:
        _handler->openAddCountryDialog(this);
        break;
    case 2:
        _handler->openAddLabelDialog(this);
        break;
    case 3:
        _handler->openAddAlbumDialog(this);
        break;
    case 4:
        _handler->openAddSongDialog(this);
        break;
    case 5:
        _handler->openAddGenreDialog(this);
        break;
    default:
        break;
    }
}

void MainWindow::onClickedRemovePushButton()
{
    int tabIndex = ui->tabWidget->currentIndex();
    int id = -1;
    TableType type = static_cast<TableType>(tabIndex);

    switch (type) {
    case TableType::artists:
        id = getSelectedId(ui->artistsTableView);
        break;
    case TableType::countries:
        id = getSelectedId(ui->countriesTableView);
        break;
    case TableType::labels:
        id = getSelectedId(ui->labelsTableView);
        break;
    case TableType::albums:
        id = getSelectedId(ui->albumsTableView);
        break;
    case TableType::songs:
        id = getSelectedId(ui->songsTableView);
        break;
    case TableType::genres:
        id = getSelectedId(ui->genresTableView);
        break;
    }

    if (id == -1) {
        QMessageBox::warning(this, tr("Внимание"), tr("Пожалуйста, выберите запись для удаления."));
        return;
    }

    RemoveDialog dialog(_db.get(), type, id, this);
    if (dialog.exec() == QDialog::Accepted)
        setupTable();
}
int MainWindow::getSelectedId(QTableView *view)
{
    auto index = view->currentIndex();
    if (!index.isValid())
        return -1;
    return view->model()->data(view->model()->index(index.row(), 0)).toInt();
}

MainWindow::~MainWindow()
{
    delete ui;
}
