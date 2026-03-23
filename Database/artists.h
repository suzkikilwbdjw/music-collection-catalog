#ifndef ARTISTS_H
#define ARTISTS_H
#include <QHash>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QString>
class Artists
{
public:
    explicit Artists(const QSqlDatabase &db);
    /// Инициализация таблицы
    /// \brief init
    ///
    void init();
    /// Создать новую запись
    /// \brief add
    /// \param model
    ///
    void add(const QHash<QString, QVariant> &values);
    /// Удалить запись
    /// \brief remove
    /// \param model
    ///
    void remove(int id);

private:
    QSqlDatabase _db;
};

#endif // ARTISTS_H
