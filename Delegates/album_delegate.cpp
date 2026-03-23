#include "album_delegate.h"

#include <QDateEdit>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QSqlQuery>
#include <QSqlRecord>

void AlbumDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    QVariant value = index.data(Qt::DisplayRole);
    if (value.isNull() || value.toString().isEmpty()) {
        QStyleOptionViewItem opt = option;
        drawBackground(painter, opt, index);
        drawDisplay(painter, opt, opt.rect, "Отсутствует");
        drawFocus(painter, opt, opt.rect);
    } else {
        QStyleOptionViewItem opt = option;
        drawBackground(painter, opt, index);
        drawDisplay(painter, opt, opt.rect, value.toString());
        drawFocus(painter, opt, opt.rect);
    }
}

void AlbumDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == 1) {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
        if (lineEdit) {
            QRegularExpression regex("[a-zA-Zа-яА-Я]+");
            lineEdit->setValidator(new QRegularExpressionValidator(regex, lineEdit));
        }
    }

    if (index.column() == 2) {
        QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
        if (dateEdit) {
            QDate date = QDate::fromString(index.data().toString(), "dd.MM.yyyy");
            dateEdit->setDate(date);
            return;
        }
    }

    // Комбобокс с выбором Лейбла
    if (index.column() == 3) {
        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        if (combo) {
            if (combo->findText("Отсутствует") == -1) {
                combo->insertItem(0, "Отсутствует", QVariant());
            }

            QSqlRelationalDelegate::setEditorData(editor, index);

            if (combo->currentIndex() < 0 || index.data().toString().isEmpty()) {
                combo->setCurrentIndex(0);
            }
            return;
        }
    }

    QSqlRelationalDelegate::setEditorData(editor, index);
}

void AlbumDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
    if (index.column() == 2) {
        QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
        if (dateEdit) {
            model->setData(index, dateEdit->date().toString("dd.MM.yyyy"));
            return;
        }
    }

    // Если поставили поле отсутствует в колоке Лебл
    if (index.column() == 3) {
        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        if (combo->currentIndex() == 0) {
            auto sqlModel = qobject_cast<QSqlRelationalTableModel *>(model);
            if (sqlModel) {
                int row = index.row();
                int id = sqlModel->record(row).value("id").toInt();

                QSqlQuery query(sqlModel->database());
                query.prepare("UPDATE Albums SET label_id = NULL WHERE id = :id");
                query.bindValue(":id", id);

                if (query.exec())
                    sqlModel->select();
            }
            return;
        }
    }

    QSqlRelationalDelegate::setModelData(editor, model, index);
}

QWidget *AlbumDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    if (index.column() == 2) {
        QDateEdit *editor = new QDateEdit(parent);
        editor->setCalendarPopup(true);
        editor->setDisplayFormat("dd.MM.yyyy");
        return editor;
    }

    return QSqlRelationalDelegate::createEditor(parent, option, index);
}
