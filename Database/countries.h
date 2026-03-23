#ifndef COUNTRIES_H
#define COUNTRIES_H
#include <QHash>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Countries
{
public:
    explicit Countries(const QSqlDatabase &db);
    void init();
    void add(const QHash<QString, QVariant> &values);
    void remove(int id);

private:
    QSqlDatabase _db;
};

#endif // COUNTRIES_H
