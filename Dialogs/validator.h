#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QList>
#include <QString>

class Validator
{
public:
    // Проверка обычной строки (не пустая)
    static bool isValidString(const QString &text) { return !text.trimmed().isEmpty(); }

    // Проверка числе в заданном диапазоне
    static bool isValidNumberInt(const QString &text, int min = 0, int max = 100000000)
    {
        bool ok;
        int value = text.toInt(&ok);
        return ok && value >= min && value <= max;
    }
    static bool isValidNumberDouble(const QString &text, double min = 0.0, double max = 10.0)
    {
        bool ok;
        double value = text.toDouble(&ok);
        return ok && value >= min && value <= max;
    }
    static bool allValid(const QList<bool> &checks)
    {
        for (bool check : checks)
            if (!check)
                return false;
        return true;
    }
};

#endif
