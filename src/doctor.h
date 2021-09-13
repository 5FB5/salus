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
    QString doctorShortName; // to get an initials from full name
    QString doctorSpecialization;
    QString institutionName;
    QString institutionCode;
    QString institutionAddress;
    QString inn;
    QString licenseInfo;

public slots:
    void saveDataToDataBase(); // for profile registration
    void loadDataFromDataBase();

private:
    QString getDoctorShortName(QString fullName);

};

#endif // DOCTOR_H
