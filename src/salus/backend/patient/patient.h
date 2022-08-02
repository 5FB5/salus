#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QFile>
#include <QFileInfo>
//#include <QDate>

class Patient
{

public:
    Patient();

    enum SexType
    {
        MAN,
        WOMAN
    };

    QString fullName;
    QString address;
    QString occupation;
    QString currentDiagnosis;
    QString anamnesis;
    QString phoneNumber;
    QString birthDate; // TODO: это должно быть QDate, но непонятно где это использовать

    bool sex;

    quint16 age;

    QList<QString> complaints; // жалобы
    QList<QString> diseases; // перенесённые заболевания

};

#endif // PATIENT_H
