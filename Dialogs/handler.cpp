#include "handler.h"
#include "Dialogs/add_album_dialog.h"
#include "Dialogs/add_artist_dialog.h"
#include "Dialogs/add_country_dialog.h"
#include "Dialogs/add_genre_dialog.h"
#include "Dialogs/add_label_dialog.h"
#include "Dialogs/add_song_dialog.h"

Handler::Handler(Database *db, QObject *parent)
    : QObject(parent)
    , _db(db)

{}

void Handler::openAddAlbumDialog(QWidget *parentWindow)
{
    AddAlbumDialog dialog(_db, parentWindow);
    if (dialog.exec() == QDialog::Accepted) {
        _db->getAlbumsModel()->select();
        auto relModel = _db->getSongsModel()->relationModel(8);
        if (relModel)
            relModel->select();
    }
}
void Handler::openAddArtistDialog(QWidget *parentWindow)
{
    AddArtistDialog dialog(_db, parentWindow);
    if (dialog.exec() == QDialog::Accepted) {
        _db->getArtistsModel()->select();
        auto relModel = _db->getSongsModel()->relationModel(2);
        if (relModel)
            relModel->select();
    }
}

void Handler::openAddCountryDialog(QWidget *parentWindow)
{
    AddCountryDialog dialog(_db, parentWindow);
    if (dialog.exec() == QDialog::Accepted) {
        _db->getCountriesModel()->select();
        auto relModel = _db->getArtistsModel()->relationModel(9);
        if (relModel)
            relModel->select();
        relModel = _db->getLabelsModel()->relationModel(2);
        if (relModel)
            relModel->select();
    }
}

void Handler::openAddLabelDialog(QWidget *parentWindow)
{
    AddLabelDialog dialog(_db, parentWindow);
    if (dialog.exec() == QDialog::Accepted) {
        _db->getLabelsModel()->select();
        auto relModel = _db->getSongsModel()->relationModel(9);
        if (relModel)
            relModel->select();
        relModel = _db->getAlbumsModel()->relationModel(3);
        if (relModel)
            relModel->select();
    }
}

void Handler::openAddSongDialog(QWidget *parentWindow)
{
    AddSongDialog dialog(_db, parentWindow);
    if (dialog.exec() == QDialog::Accepted) {
        _db->getSongsModel()->select();
        auto relModel = _db->getArtistsModel()->relationModel(8);
        if (relModel)
            relModel->select();
    }
}

void Handler::openAddGenreDialog(QWidget *parentWindow)
{
    AddGenreDialog dialog(_db, parentWindow);
    if (dialog.exec() == QDialog::Accepted) {
        _db->getGenresModel()->select();
        auto relModel = _db->getSongsModel()->relationModel(10);
        if (relModel)
            relModel->select();
    }
}
