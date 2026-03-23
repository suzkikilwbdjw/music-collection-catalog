#include "database.h"
#include <QDebug>

Database::Database(const QString &pathToDatabase)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");

    // Устанавливаем путь к БД
    _db.setDatabaseName(pathToDatabase);
    if (_db.open()) {
        QSqlQuery query;
        query.exec("PRAGMA foreign_keys = ON;");
    } else {
        return;
    }
    // Создаем таблицы
    try {
        _countries = new Countries(_db);
        _genres = new Genres(_db);
        _labels = new Labels(_db);
        _artists = new Artists(_db);
        _albums = new Albums(_db);
        _songs = new Songs(_db);
    } catch (const std::exception &e) {
        qDebug() << "Ошибка: " << e.what();
    }

    // Создаем модели
    _artistsModel = new QSqlRelationalTableModel();
    _albumsModel = new QSqlRelationalTableModel();
    _countriesModel = new QSqlRelationalTableModel();
    _genresModel = new QSqlRelationalTableModel();
    _labelsModel = new QSqlRelationalTableModel();
    _songsModel = new QSqlRelationalTableModel();
}
