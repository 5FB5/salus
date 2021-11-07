#ifndef BACKEND_H
#define BACKEND_H

#include <QString>
#include <QObject>

#include "doctordatabase.h"
#include "patientdb.h"

/*! Backend class for working with QML frontend */
class Backend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString currentDoctorInn READ getCurrentDoctorInn)
    Q_PROPERTY(QString currentPatientInsuranceNumber READ getCurrentPatientInsuranceNumber)
//    Q_PROPERTY(QString doctorFullName READ getDoctorFullName)
//    Q_PROPERTY(QString doctorSpecialization READ getDoctorSpecialization)
//    Q_PROPERTY(QString doctorInsitutionName READ getDoctorInsitutionName)
//    Q_PROPERTY(QString doctorInsitutionCode READ getDoctorInsitutionCode)
//    Q_PROPERTY(QString doctorInstitutionAddress READ getDoctorInstitutionAddress)
//    Q_PROPERTY(QString doctorInn READ getDoctorInn)
//    Q_PROPERTY(QString doctorLicenseInfo READ getDoctorLicenseInfo)

public:
    Backend();

    DoctorDataBase doctorDb;
    patientDB patient;

    /*! Key of current doctor's profile */
    QString currentDoctorInn;
    QString currentPatientInsuranceNumber;

    QString getCurrentDoctorInn();

    QString getCurrentPatientInsuranceNumber();


//    QString getDoctorFullName();
//    QString getDoctorSpecialization();
//    QString getDoctorInstitutionName();
//    QString getDoctorInstitutionCode();
//    QString getDoctorInstitutionAddress();
//    QString getDoctorInn();
//    QString getDoctorLicenseInfo();

signals:
    void setDoctorProfile(QString inn);
    void setPatientProfile(QString insuranceNumber);

public slots:
    void addNewPatient(  QString fullName, quint8 age,
                         bool sex,
                         QDate birthDate,
                         QString adress,
                         QString insuranceCompany,
                         QString insuranceNumber,
                         QString phoneNumber,
                         QString occupation,
                         QString diagnosis,
                         QList<QString> diseases,
                         QString diseaseDescription);

    void addNewDoctorProfile(QString doctorFullName, QString doctorSpecialization,
                             QString doctorInstitutionName, QString doctorInstitutionCode,
                             QString doctorInstitutionAddress, QString doctorInn,
                             QString doctorLicenseInfo);

    void selectProfile(QString inn);
    void selectPatientProfile(QString insuranceNumber);

};

#endif // BACKEND_H
