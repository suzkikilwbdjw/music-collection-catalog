#include "countries.h"

Countries::Countries(const QSqlDatabase &db)
    : _db(db)
{
    init();
}

void Countries::init()
{
    QSqlQuery query;
    if (query.exec("CREATE TABLE IF NOT EXISTS Countries(id INTEGER PRIMARY KEY, name TEXT NOT "
                   "NULL UNIQUE)")) {
    } else {
        throw std::runtime_error("Не удалось создать таблицу Страны");
    }
}

void Countries::add(const QHash<QString, QVariant> &values)
{
    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO Countries(name) VALUES(:name)");
    query.bindValue(":name", values["country_name"]);
    if (!query.exec())
        throw std::runtime_error("Ошибка добавления данных в таблицу Cтраны");
}

void Countries::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Countries WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec())
        throw std::runtime_error("Ошибка удаления записи из талицы Страны");
}
