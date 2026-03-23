#include "artist_delegate.h"
#include "Widgets/date_or_present_editor.h"

#include <QDateEdit>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QSqlQuery>
#include <QSqlRecord>

void ArtistDelegate::paint(QPainter *painter,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index) const
{
    QVariant value = index.data(Qt::DisplayRole);

    if (value.isNull() || value.toString().isEmpty()) {
        QStyleOptionViewItem opt = option;
        drawBackground(painter, opt, index);
        drawDisplay(painter, opt, opt.rect, index.column() == 7 ? "По н.в." : "Отсутствует");
        drawFocus(painter, opt, opt.rect);
    } else {
        QStyleOptionViewItem opt = option;
        drawBackground(painter, opt, index);
        drawDisplay(painter, opt, opt.rect, value.toString());
        drawFocus(painter, opt, opt.rect);
    }
}

void ArtistDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    // Имя фамилия отчество, только текст
    if (index.column() == 1 || index.column() == 2 || index.column() == 3) {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
        if (lineEdit) {
            QRegularExpression regex("^[A-Za-zА-Яа-яЁё\\s-]+$");
            lineEdit->setValidator(new QRegularExpressionValidator(regex, lineEdit));
        }
    }

    // Дата рождения, старт карьеры
    if (index.column() == 5 || index.column() == 6) {
        QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
        if (dateEdit) {
            QDate date = QDate::fromString(index.data().toString(), "dd.MM.yyyy");
            dateEdit->setDate(date);
            return;
        }
    }

    // Конец карьеры
    if (index.column() == 7) {
        DateOrPresentEditor *customEditor = qobject_cast<DateOrPresentEditor *>(editor);
        if (customEditor) {
            customEditor->setDate(index.data(Qt::EditRole));
            return;
        }
    }

    // Самая популярная песня
    if (index.column() == 8) {
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

void ArtistDelegate::setModelData(QWidget *editor,
                                  QAbstractItemModel *model,
                                  const QModelIndex &index) const
{
    if (index.column() == 5 || index.column() == 6) {
        QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
        if (dateEdit) {
            model->setData(index, dateEdit->date().toString("dd.MM.yyyy"));
            return;
        }
    }

    if (index.column() == 7) {
        DateOrPresentEditor *customEditor = qobject_cast<DateOrPresentEditor *>(editor);
        if (customEditor) {
            model->setData(index, customEditor->date(), Qt::EditRole);
            return;
        }
    }

    if (index.column() == 8) {
        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        if (combo->currentIndex() == 0) {
            auto sqlModel = qobject_cast<QSqlRelationalTableModel *>(model);
            if (sqlModel) {
                int row = index.row();
                int id = sqlModel->record(row).value("id").toInt();

                QSqlQuery query(sqlModel->database());
                query.prepare("UPDATE Artists SET popular_song_id = NULL WHERE id = :id");
                query.bindValue(":id", id);

                if (query.exec())
                    sqlModel->select();
            }
            return;
        }
    }

    QSqlRelationalDelegate::setModelData(editor, model, index);
}

QWidget *ArtistDelegate::createEditor(QWidget *parent,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const
{
    if (index.column() == 5 || index.column() == 6) {
        QDateEdit *editor = new QDateEdit(parent);
        editor->setCalendarPopup(true);
        editor->setDisplayFormat("dd.MM.yyyy");
        return editor;
    }

    if (index.column() == 7) {
        return new DateOrPresentEditor(parent);
    }

    return QSqlRelationalDelegate::createEditor(parent, option, index);
}
