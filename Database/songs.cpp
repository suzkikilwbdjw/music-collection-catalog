#include "songs.h"

Songs::Songs(const QSqlDatabase &db)
    : _db(db)
{
    init();
}

void Songs::init()
{
    QSqlQuery query;
    if (query.exec("CREATE TABLE IF NOT EXISTS Songs(id INTEGER PRIMARY KEY, name TEXT NOT "
                   "NULL,artist_id INTEGER NOT NULL, "
                   "date_of_create TEXT NOT NULL,duration INTEGER NOT NULL,rating REAL NOT NULL, "
                   "text TEXT NOT NULL, number_of_auditions INT NOT NULL, album_id INTEGER"
                   ", label_id INTEGER , genre_id INTEGER NOT NULL, FOREIGN KEY (artist_id) "
                   "REFERENCES "
                   "Artists(id),FOREIGN KEY (album_id) REFERENCES Albums(id), "
                   "FOREIGN KEY (label_id) REFERENCES Labels(id), FOREIGN KEY (genre_id) "
                   "REFERENCES Genres(id))")) {
    } else {
        throw std::runtime_error("Не удалось создать таблицу Артисты");
    }
}

void Songs::add(const QHash<QString, QVariant> &values)
{
    // Начинаем транзакцию
    _db.transaction();
    try {
        QSqlQuery query;

        // Получаем id Артиста
        query.prepare("SELECT id FROM Artists WHERE nickname = :nickname");
        query.bindValue(":nickname", values["nickname"]);
        if (!query.exec() || !query.next())
            throw std::runtime_error("Не удалось получить ID артиста");
        int artistdId = query.value(0).toInt();

        // Получаем id Альбома
        QVariant albumId = QVariant(QVariant::Int);
        if (!values["album_name"].toString().isEmpty()) {
            query.prepare("SELECT id FROM Albums WHERE name = :album_name");
            query.bindValue(":album_name", values["album_name"]);
            if (query.exec() && query.next()) {
                albumId = query.value(0).toInt();
            } else {
                throw std::runtime_error("Указанный альбом не найден");
            }
        }

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

        // Получаем id Жанра
        query.prepare("SELECT id FROM Genres WHERE name = :genre_name");
        query.bindValue(":genre_name", values["genre_name"]);
        if (!query.exec() || !query.next())
            throw std::runtime_error("Не удалось получить ID жанра");
        int genreId = query.value(0).toInt();

        query.prepare(
            "INSERT INTO Songs(name, artist_id, date_of_create, duration, rating, text, "
            "number_of_auditions, album_id, label_id, genre_id) VALUES(:name, "
            ":artist_id, :date_of_create, "
            ":duration, :rating, :text, :number_of_auditions, :album_id, :label_id, :genre_id)");
        query.bindValue(":name", values["song_name"]);
        query.bindValue(":artist_id", artistdId);
        query.bindValue(":date_of_create", values["date_of_create"]);
        query.bindValue(":duration", values["duration"]);
        query.bindValue(":rating", values["rating"]);
        query.bindValue(":text", values["text"]);
        query.bindValue(":number_of_auditions", values["number_of_auditions"]);
        query.bindValue(":album_id", albumId);
        query.bindValue(":label_id", labelId);
        query.bindValue(":genre_id", genreId);

        if (!query.exec())
            throw std::runtime_error("Не удалось добавить запись в Песни");
        _db.commit();

    } catch (const std::exception &e) {
        _db.rollback();
        throw;
    }
}

void Songs::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Songs WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec())
        throw std::runtime_error("Ошибка удаления записи из талицы Песни");
}
