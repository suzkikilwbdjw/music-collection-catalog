#include "date_or_present_editor.h"

DateOrPresentEditor::DateOrPresentEditor(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    dateEdit = new QDateEdit(this);
    checkBox = new QCheckBox("по н.в.", this);

    dateEdit->setCalendarPopup(true);
    layout->addWidget(dateEdit);
    layout->addWidget(checkBox);
    layout->setContentsMargins(2, 0, 2, 0);
    layout->setSpacing(5);

    connect(checkBox, &QCheckBox::toggled, dateEdit, &QDateEdit::setDisabled);
    setFocusProxy(dateEdit);
}

void DateOrPresentEditor::setDate(const QVariant &data)
{
    if (data.isNull() || !data.isValid()) {
        checkBox->setChecked(true);
        dateEdit->setDate(QDate::currentDate());
    } else {
        checkBox->setChecked(false);
        dateEdit->setDate(data.toDate());
    }
}

QVariant DateOrPresentEditor::date() const
{
    if (checkBox->isChecked())
        return QVariant();
    return dateEdit->date();
}
