#include <QCheckBox>
#include <QDateEdit>
#include <QHBoxLayout>

class DateOrPresentEditor : public QWidget
{
    Q_OBJECT
public:
    explicit DateOrPresentEditor(QWidget *parent = nullptr);

    void setDate(const QVariant &data);

    QVariant date() const;

private:
    QDateEdit *dateEdit;
    QCheckBox *checkBox;
};
