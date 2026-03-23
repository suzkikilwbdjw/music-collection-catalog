#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include "albums.h"
#include "artists.h"
#include "countries.h"
#include "genres.h"
#include "labels.h"
#include "songs.h"

class Database
{
public:
    explicit Database(const QString &pathToDatabase);

    Artists *getArtists() const { return _artists; };
    Albums *getAlbums() const { return _albums; };
    Labels *getLabels() const { return _labels; }
    Genres *getGenres() const { return _genres; }
    Songs *getSongs() const { return _songs; }
    Countries *getCountries() const { return _countries; }

    QSqlRelationalTableModel *getCountriesModel() { return _countriesModel; }
    QSqlRelationalTableModel *getArtistsModel() { return _artistsModel; };
    QSqlRelationalTableModel *getAlbumsModel() { return _albumsModel; };
    QSqlRelationalTableModel *getLabelsModel() { return _labelsModel; }
    QSqlRelationalTableModel *getGenresModel() { return _genresModel; }
    QSqlRelationalTableModel *getSongsModel() { return _songsModel; }

private:
    QSqlDatabase _db;
    Artists *_artists;
    Countries *_countries;
    Genres *_genres;
    Labels *_labels;
    Songs *_songs;
    Albums *_albums;
    /* ============Модели таблиц============ */
    QSqlRelationalTableModel *_artistsModel;
    QSqlRelationalTableModel *_albumsModel;
    QSqlRelationalTableModel *_countriesModel;
    QSqlRelationalTableModel *_genresModel;
    QSqlRelationalTableModel *_labelsModel;
    QSqlRelationalTableModel *_songsModel;
    /* ===================================== */
};

#endif // DATABASE_H
