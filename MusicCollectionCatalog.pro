QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Database/albums.cpp \
    Database/artists.cpp \
    Database/countries.cpp \
    Database/database.cpp \
    Database/genres.cpp \
    Database/labels.cpp \
    Database/songs.cpp \
    Delegates/album_delegate.cpp \
    Delegates/artist_delegate.cpp \
    Delegates/country_delegate.cpp \
    Delegates/genre_delegate.cpp \
    Delegates/song_delegate.cpp \
    Dialogs/add_album_dialog.cpp \
    Dialogs/add_artist_dialog.cpp \
    Dialogs/add_country_dialog.cpp \
    Dialogs/add_genre_dialog.cpp \
    Dialogs/add_label_dialog.cpp \
    Dialogs/add_song_dialog.cpp \
    Dialogs/handler.cpp \
    Dialogs/validator.cpp \
    main.cpp \
    mainwindow.cpp \
    Dialogs/remove_dialog.cpp \
    Widgets/date_or_present_editor.cpp

HEADERS += \
    Database/albums.h \
    Database/artists.h \
    Database/countries.h \
    Database/database.h \
    Database/genres.h \
    Database/labels.h \
    Database/songs.h \
    Delegates/album_delegate.h \
    Delegates/artist_delegate.h \
    Delegates/country_delegate.h \
    Delegates/genre_delegate.h \
    Delegates/song_delegate.h \
    Dialogs/add_album_dialog.h \
    Dialogs/add_artist_dialog.h \
    Dialogs/add_country_dialog.h\
    Dialogs/add_genre_dialog.h \
    Dialogs/add_label_dialog.h \
    Dialogs/add_song_dialog.h \
    Dialogs/handler.h \
    Dialogs/validator.h \
    mainwindow.h \
    Dialogs/remove_dialog.h \
    table_type.h \
    Widgets/date_or_present_editor.h

FORMS += \
    Dialogs/add_album_dialog.ui \
    Dialogs/add_artist_dialog.ui \
    Dialogs/add_country_dialog.ui\
    Dialogs/add_genre_dialog.ui \
    Dialogs/add_label_dialog.ui \
    Dialogs/add_song_dialog.ui \
    mainwindow.ui \
    Dialogs/remove_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
