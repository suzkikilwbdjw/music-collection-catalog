#include "labels.h"

Labels::Labels(const QSqlDatabase &db)
    : _db(db)
{
    init();
}

void Labels::init()
{
    QSqlQuery query;
    if (query.exec("CREATE TABLE IF NOT EXISTS Labels(id INTEGER PRIMARY KEY, name TEXT NOT NULL, "
                   "country_id INT NOT NULL, FOREIGN KEY (country_id) REFERENCES Countries(id))")) {
    } else {
        throw std::runtime_error("Не удалось создать таблицу Артисты");
    }
}

void Labels::add(const QHash<QString, QVariant> &values)
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

        // Запрос на вставку данных в таблицу Лейблы
        query.prepare("INSERT INTO Labels(name, country_id) "
                      "VALUES(:name, :country_id)");
        query.bindValue(":name", values["label_name"]);
        query.bindValue(":country_id", countryId);
        if (!query.exec())
            throw std::runtime_error("Не удалось создать запись в таблице Лейблы");
        _db.commit();
    } catch (const std::exception &e) {
        _db.rollback();
    }
}

void Labels::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Labels WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec())
        throw std::runtime_error("Ошибка удаления записи из талицы Лейблы");
}
