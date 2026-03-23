#ifndef COUNTRY_DELEGATE_H
#define COUNTRY_DELEGATE_H
#include <QSqlRelationalDelegate>

class CountryDelegate : public QSqlRelationalDelegate
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

#endif // COUNTRY_DELEGATE_H
