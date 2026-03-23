#include "country_delegate.h"

#include <QLineEdit>
#include <QRegularExpressionValidator>

void CountryDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == 1) {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
        if (lineEdit) {
            QRegularExpression regex("[a-zA-Zа-яА-Я]+");
            lineEdit->setValidator(new QRegularExpressionValidator(regex, lineEdit));
        }
    }
    QSqlRelationalDelegate::setEditorData(editor, index);
}

void CountryDelegate::setModelData(QWidget *editor,
                                   QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QSqlRelationalDelegate::setModelData(editor, model, index);
}

QWidget *CountryDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const
{
    return QSqlRelationalDelegate::createEditor(parent, option, index);
}
