#ifndef SONGS_H
#define SONGS_H
#include <QHash>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Songs
{
public:
    explicit Songs(const QSqlDatabase &db);
    void init();
    void add(const QHash<QString, QVariant> &values);
    void remove(int id);

private:
    QSqlDatabase _db;
};

#endif // SONGS_H
