#include "genres.h"

Genres::Genres(const QSqlDatabase &db)
    : _db(db)
{
    init();
}

void Genres::init()
{
    QSqlQuery query;
    if (query.exec("CREATE TABLE IF NOT EXISTS Genres(id INTEGER PRIMARY KEY, name TEXT NOT NULL "
                   "UNIQUE)")) {
    } else {
        throw std::runtime_error("Не удалось создать таблицу Жанры");
    }
}

void Genres::add(const QHash<QString, QVariant> &values)
{
    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO Genres(name) VALUES(:name)");
    query.bindValue(":name", values["genre_name"]);
    if (!query.exec())
        throw std::runtime_error("Ошибка добавления данных в таблицу Жанры");
}

void Genres::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Genres WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec())
        throw std::runtime_error("Ошибка удаления записи из талицы Жанры");
}
