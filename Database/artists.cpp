#include "artists.h"
#include <QSqlQuery>

Artists::Artists(const QSqlDatabase &db)
    : _db(db)
{
    init();
}

void Artists::init()
{
    QSqlQuery query;
    if (query.exec("CREATE TABLE IF NOT EXISTS Artists ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "second_name TEXT NOT NULL, "
                   "first_name TEXT NOT NULL, "
                   "patronymic TEXT, "
                   "nickname TEXT NOT NULL, "
                   "date_of_birth TEXT NOT NULL, "
                   "career_start_date TEXT NOT NULL, "
                   "career_end_date TEXT, "
                   "popular_song_id INTEGER, "
                   "country_id INTEGER NOT NULL, "
                   "FOREIGN KEY (popular_song_id) REFERENCES Songs(id), "
                   "FOREIGN KEY (country_id) REFERENCES Countries(id)"
                   ")")) {
    } else {
        throw std::runtime_error("Не удалось создать таблицу Артисты");
    }
}

void Artists::add(const QHash<QString, QVariant> &values)
{
    // Начинаем транзакцию
    _db.transaction();
    try {
        QSqlQuery query;

        // Получаем id Страны
        query.prepare("SELECT id FROM Countries WHERE name = :name");
        query.bindValue(":name", values["country_name"]);
        if (!query.exec() || !query.next())
            throw std::runtime_error("Не удалось получить ID страны");

        int countryId = query.value(0).toInt();

        // Запрос на вставку данных в таблицу Артисты
        query.prepare(
            "INSERT INTO Artists(second_name, first_name, patronymic, nickname,date_of_birth, "
            "career_start_date, career_end_date, popular_song_id,country_id) "
            "VALUES(:second_name, :first_name, :patronymic, :nickname, :date_of_birth, "
            ":career_start_date, :career_end_date, :popular_song_id, :country_id)");
        query.bindValue(":second_name", values["second_name"]);
        query.bindValue(":first_name", values["first_name"]);
        query.bindValue(":patronymic", values["patronymic"]);
        query.bindValue(":nickname", values["nickname"]);
        query.bindValue(":date_of_birth", values["date_of_birth"]);
        query.bindValue(":career_start_date", values["career_start_date"]);
        query.bindValue(":career_end_date", values["career_end_date"]);
        query.bindValue(":popular_song_id", values["popular_song_id"]);
        query.bindValue(":country_id", countryId);
        if (!query.exec())
            throw std::runtime_error("Не удалось создать запись в таблице Артисты");
        _db.commit();
    } catch (const std::exception &e) {
        _db.rollback();
    }
}

void Artists::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Artists WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec())
        throw std::runtime_error("Ошибка удаления записи из таблицы Артисты");
}
