#ifndef DOCTOR_H
#define DOCTOR_H

#include <QString>
#include <QList>

class Doctor
{

public:
    Doctor();

    QString fullName, specialization, institutionName, institutionAddress, licenseInfo, initials;
    quint16 institutionCode, inn;

};

#endif // DOCTOR_H
