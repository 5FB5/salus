#ifndef DOCTOR_H
#define DOCTOR_H

#include <QObject>
#include <QString>

class Doctor : public QObject
{
    Q_OBJECT

public:
    explicit Doctor(QObject *parent = nullptr);

    QString doctorFullName;
    QString doctorSpecialization;
    QString institutionName;
    QString institutionCode;
    QString institutionAddress;
    QString inn;
    QString licenseInfo;

    QString getDoctorShortName(QString fullName); // to get an initials from full name

    void loadDataFromDataBase();

public slots:
    void saveDataToJson(); // for profile registration

};

#endif // DOCTOR_H
