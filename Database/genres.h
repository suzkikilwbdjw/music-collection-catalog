#ifndef GENRES_H
#define GENRES_H
#include <QHash>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Genres
{
public:
    explicit Genres(const QSqlDatabase &db);
    void init();
    void add(const QHash<QString, QVariant> &values);
    void remove(int id);

private:
    QSqlDatabase _db;
};

#endif // GENRES_H
