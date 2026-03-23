#ifndef ALBUMS_H
#define ALBUMS_H
#include <QHash>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

class Albums
{
public:
    explicit Albums(const QSqlDatabase &db);
    void init();
    void add(const QHash<QString, QVariant> &values);
    void remove(int id);
    void update(int id, const QHash<QString, QVariant> &values);

private:
    QSqlDatabase _db;
};

#endif // ALBUMS_H
