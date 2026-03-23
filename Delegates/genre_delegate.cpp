#include "genre_delegate.h"

#include <QLineEdit>
#include <QRegularExpressionValidator>

void GenreDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
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

void GenreDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
    QSqlRelationalDelegate::setModelData(editor, model, index);
}

QWidget *GenreDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    return QSqlRelationalDelegate::createEditor(parent, option, index);
}
