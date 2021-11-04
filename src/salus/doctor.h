#ifndef DOCTOR_H
#define DOCTOR_H

#include <QString>
#include <QList>

class Doctor
{

public:
    Doctor();

    QString fullName;
    QString specialization;
    QString institutionName;
    QString institutionCode;
    QString institutionAddress;
    QString inn;
    QString licenseInfo;

    QList<QString> diagnoses, treatments;

};

#endif // DOCTOR_H
