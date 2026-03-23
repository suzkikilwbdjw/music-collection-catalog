#ifndef LABELS_H
#define LABELS_H
#include <QHash>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Labels
{
public:
    explicit Labels(const QSqlDatabase &db);
    void init();
    void add(const QHash<QString, QVariant> &values);
    void remove(int id);

private:
    QSqlDatabase _db;
};

#endif // LABELS_H
