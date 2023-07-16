#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QFile>
#include <QFileInfo>

class Patient
{

public:
    struct Record_t
    {
        QString date; // дата записи
        QString currentDiagnosis; // диагноз
        QString anamnesis; // анамнез
        QString treatment; // лечение
        QString complaints; // жалобы
        QString treatmentResult; // результаты лечения
        QString diseases; // перенесённые заболевания FIXME: временно используется для хранения данных исследования
    };

    enum SexType
    {
        MAN,
        WOMAN
    };

    Patient();

    QString fullName;
    QString address;
    QString occupation;
    QString phoneNumber;
    QString birthDate; // TODO: это должно быть QDate, но непонятно где это использовать

    bool sex;
    int age;

    QList<Record_t> cardRecords;

};

#endif // PATIENT_H
