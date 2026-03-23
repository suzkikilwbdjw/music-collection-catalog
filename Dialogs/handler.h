#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <QObject>
#include "Database/database.h"

class Handler : public QObject
{
    Q_OBJECT
public:
    explicit Handler(Database *db, QObject *parent = nullptr);

private:
    Database *_db;

public:
    void openAddAlbumDialog(QWidget *parentWindow);
    void openAddArtistDialog(QWidget *parentWindow);
    void openAddCountryDialog(QWidget *parentWindow);
    void openAddGenreDialog(QWidget *parentWindow);
    void openAddSongDialog(QWidget *parentWindow);
    void openAddLabelDialog(QWidget *parentWindow);
};

#endif // EVENT_HANDLER_H
