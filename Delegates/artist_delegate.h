#ifndef ARTIST_DELEGATE_H
#define ARTIST_DELEGATE_H
#include <QSqlRelationalDelegate>

class ArtistDelegate : public QSqlRelationalDelegate
{
public:
    using QSqlRelationalDelegate::QSqlRelationalDelegate;

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;
};

#endif // ARTIST_DELEGATE_H
