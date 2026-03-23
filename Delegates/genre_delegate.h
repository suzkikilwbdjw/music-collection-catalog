#ifndef GENRE_DELEGATE_H
#define GENRE_DELEGATE_H
#include <QSqlRelationalDelegate>

class GenreDelegate : public QSqlRelationalDelegate
{
public:
    using QSqlRelationalDelegate::QSqlRelationalDelegate;

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;
};

#endif // GENRE_DELEGATE_H
