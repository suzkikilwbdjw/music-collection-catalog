#include "albums.h"

Albums::Albums(const QSqlDatabase &db)
    : _db(db)
{
    init();
}

void Albums::init()
{
    QSqlQuery query;
    if (query.exec("CREATE TABLE IF NOT EXISTS Albums(id INTEGER PRIMARY KEY, name TEXT NOT NULL, "
                   "date_of_release TEXT NOT NULL, label_id INT , FOREIGN KEY (label_id) "
                   "REFERENCES Labels(id))")) {
    } else {
        throw std::runtime_error("Не удалось создать таблицу Альбомов");
    }
}

void Albums::add(const QHash<QString, QVariant> &values)
{
    // Начинаем транзакцию
    _db.transaction();
    try {
        QSqlQuery query;

        // Получаем id Лейбла
        QVariant labelId = QVariant(QVariant::Int);
        if (!values["label_name"].toString().isEmpty()) {
            query.prepare("SELECT id FROM Labels WHERE name = :label_name");
            query.bindValue(":label_name", values["label_name"]);
            if (query.exec() && query.next()) {
                labelId = query.value(0).toInt();
            } else {
                throw std::runtime_error("Указанный лейбл не найден");
            }
        }

        // Запрос на вставку данных в таблицу Aльбомы
        query.prepare("INSERT INTO Albums(name, date_of_release, label_id) VALUES(:name, "
                      ":date_of_release, :label_id)");
        query.bindValue(":name", values["album_name"]);
        query.bindValue(":date_of_release", values["date_of_release"]);
        query.bindValue(":label_id", labelId);

        if (!query.exec())
            throw std::runtime_error("Не удалось создать запись в таблице Альбомы");
        _db.commit();
    } catch (const std::exception &e) {
        _db.rollback();
        throw std::runtime_error("Не удалось получить ID лейбла");
    }
}

void Albums::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Albums WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec())
        throw std::runtime_error("Ошибка удаления записи из талицы Альбомы");
}

void Albums::update(int id, const QHash<QString, QVariant> &values)
{
    QSqlQuery query;
}
