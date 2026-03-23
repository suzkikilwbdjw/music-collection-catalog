#include "song_delegate.h"

#include <QDateEdit>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QSqlQuery>
#include <QSqlRecord>

void SongDelegate::paint(QPainter *painter,
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

void SongDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    // Комбобокс с выбором Альбома
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
    // Комбобокс с выбором Лейбла
    if (index.column() == 9) {
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

    if (index.column() == 3) {
        QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
        if (dateEdit) {
            QDate date = QDate::fromString(index.data().toString(), "dd.MM.yyyy");
            dateEdit->setDate(date);
            return;
        }
    }

    QSqlRelationalDelegate::setEditorData(editor, index);
}

void SongDelegate::setModelData(QWidget *editor,
                                QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    // Если поставили поле отсутствует в колонке Альбом
    if (index.column() == 8) {
        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        if (combo->currentIndex() == 0) {
            auto sqlModel = qobject_cast<QSqlRelationalTableModel *>(model);
            if (sqlModel) {
                int row = index.row();
                int id = sqlModel->record(row).value("id").toInt();

                QSqlQuery query(sqlModel->database());
                query.prepare("UPDATE Songs SET album_id = NULL WHERE id = :id");
                query.bindValue(":id", id);

                if (query.exec())
                    sqlModel->select();
            }
            return;
        }
    }

    // Если поставили поле отсутствует в колоке Лебл
    if (index.column() == 9) {
        QComboBox *combo = qobject_cast<QComboBox *>(editor);
        if (combo->currentIndex() == 0) {
            auto sqlModel = qobject_cast<QSqlRelationalTableModel *>(model);
            if (sqlModel) {
                int row = index.row();
                int id = sqlModel->record(row).value("id").toInt();

                QSqlQuery query(sqlModel->database());
                query.prepare("UPDATE Songs SET label_id = NULL WHERE id = :id");
                query.bindValue(":id", id);

                if (query.exec())
                    sqlModel->select();
            }
            return;
        }
    }

    // При редaктировании даты ввыпуска
    if (index.column() == 3) {
        QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
        if (dateEdit) {
            model->setData(index, dateEdit->date().toString("dd.MM.yyyy"));
            return;
        }
    }

    QSqlRelationalDelegate::setModelData(editor, model, index);
}

QWidget *SongDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    QWidget *editor = QSqlRelationalDelegate::createEditor(parent, option, index);

    if (QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox *>(editor)) {
        spinBox->setRange(0.0, 10.0);
        spinBox->setDecimals(2);
        return spinBox;
    }

    // Длительность
    if (index.column() == 4) {
        QSpinBox *spinBox = new QSpinBox(parent);
        spinBox->setRange(0, 10000);
        return spinBox;
    }

    // Количество прослушиваний
    if (index.column() == 7) {
        QSpinBox *spinBox = new QSpinBox(parent);
        spinBox->setRange(0, 1000000000);
        return spinBox;
    }

    // Дата выпуска
    if (index.column() == 3) {
        QDateEdit *editor = new QDateEdit(parent);
        editor->setCalendarPopup(true);
        editor->setDisplayFormat("dd.MM.yyyy");
        return editor;
    }

    return QSqlRelationalDelegate::createEditor(parent, option, index);
}
