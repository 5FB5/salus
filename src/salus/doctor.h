#ifndef DOCTOR_H
#define DOCTOR_H

#include <QString>
#include <QList>

class Doctor
{

public:
    Doctor();

    QString fullName, specialization, institutionName, institutionAddress, licenseInfo;

    quint16 institutionCode, inn;

    QList<QString> diagnoses, treatments;

};

#endif // DOCTOR_H
