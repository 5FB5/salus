#ifndef BACKEND_H
#define BACKEND_H

#include <QString>
#include <QObject>

#include "doctordatabase.h"
#include "patientdb.h"

/*! Class for working with QML frontend */
class Backend : public QObject
{
    Q_OBJECT

    // Properties for accessing to current doctor's data from QML
    Q_PROPERTY(QString currentDoctorFullName READ getCurrentDoctorFullName) // WRITE setCurrentDoctorFullname)
    Q_PROPERTY(QString currentDoctorSpecialization READ getCurrentDoctorSpecialization) // WRITE setCurrentDoctorSpecialization)
    Q_PROPERTY(QString currentDoctorInstitutionName READ getCurrentDoctorInstitutionName) // WRITE setCurrentDoctorInstitutionName)
    Q_PROPERTY(QString currentDoctorInstitutionCode READ getCurrentDoctorInstitutionCode) // WRITE setCurrentDoctorInstitutionCode)
    Q_PROPERTY(QString currentDoctorInstitutionAddress READ getCurrentDoctorInstitutionAddress) // WRITE setCurrentDoctorInstitutionAddress)
    Q_PROPERTY(QString currentDoctorInn READ getCurrentDoctorInn) // WRITE setCurrentDoctorInn)
    Q_PROPERTY(QString currentDoctorLicenseInfo READ getCurrentDoctorLicenseInfo) // WRITE setCurrentDoctorLicenseInfo)
    Q_PROPERTY(QString currentDoctorInitials READ getCurrentDoctorInitials)

    Q_PROPERTY(bool isDoctorDbEmpty READ getIsDoctorDbExists)

public:
    explicit Backend(QObject *parent = nullptr);

    /*! Global class for accessing the doctor's database */
    DoctorDataBase doctorDb;
    patientDB patient;

    /*!
     *  Stores INN value of selected doctor's profile as current.
     *  Can be used as primary key to access another data
    */
    QString currentDoctorInn;

    QString getCurrentDoctorFullName();
    QString getCurrentDoctorSpecialization();
    QString getCurrentDoctorInstitutionName();
    QString getCurrentDoctorInstitutionCode();
    QString getCurrentDoctorInstitutionAddress();

    QString getCurrentDoctorInn();

    QString getCurrentDoctorLicenseInfo();
    QString getCurrentDoctorInitials();

    /*! Returns true if doctor's database doesn't have any profiles */
    bool getIsDoctorDbExists();

signals:
    void setPatientProfile(QString insuranceNumber);
    void changeDoctorProfile();

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

    void setCurrentDoctorInn(QString inn);
};

#endif // BACKEND_H
