#ifndef BACKEND_H
#define BACKEND_H

#include <QString>
#include <QObject>

#include "doctordatabase.h"

/*! Backend class for working with QML frontend */
class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString currentDoctorInn READ getCurrentDoctorInn)
    Q_PROPERTY(bool isDoctorDbEmpty READ getIsDoctorDbExists)

//    Q_PROPERTY(QString doctorFullName READ getDoctorFullName)
//    Q_PROPERTY(QString doctorSpecialization READ getDoctorSpecialization)
//    Q_PROPERTY(QString doctorInsitutionName READ getDoctorInsitutionName)
//    Q_PROPERTY(QString doctorInsitutionCode READ getDoctorInsitutionCode)
//    Q_PROPERTY(QString doctorInstitutionAddress READ getDoctorInstitutionAddress)
//    Q_PROPERTY(QString doctorInn READ getDoctorInn)
//    Q_PROPERTY(QString doctorLicenseInfo READ getDoctorLicenseInfo)

public:
    explicit Backend(QObject *parent = nullptr);

    DoctorDataBase doctorDb;

    /*! Key of current doctor's profile */
    QString currentDoctorInn;
    QString getCurrentDoctorInn();

    //For QML to check that we doesn't have a doctor's DB file
    bool isDoctorDbEmpty;
    // For Q_PROPERTY
    bool getIsDoctorDbExists();

//    QString getDoctorFullName();
//    QString getDoctorSpecialization();
//    QString getDoctorInstitutionName();
//    QString getDoctorInstitutionCode();
//    QString getDoctorInstitutionAddress();
//    QString getDoctorInn();
//    QString getDoctorLicenseInfo();

signals:
    void setDoctorProfile(QString inn);

public slots:
    void addNewDoctorProfile(QString doctorFullName, QString doctorSpecialization,
                             QString doctorInstitutionName, QString doctorInstitutionCode,
                             QString doctorInstitutionAddress, QString doctorInn,
                             QString doctorLicenseInfo);

    void selectProfile(QString inn);
};

#endif // BACKEND_H
