#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QFile>
#include <QFileInfo>

#include "patientcardrecord.h"

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
    QString phoneNumber;
    QString birthDate; // TODO: это должно быть QDate, но непонятно где это использовать

    bool sex;

    quint16 age;

    QList<Record> cardRecords;

};

#endif // PATIENT_H
