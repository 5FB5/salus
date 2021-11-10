#ifndef BACKEND_H
#define BACKEND_H

#include <QString>
#include <QObject>

#include "doctordatabase.h"

/*! Class for working with QML frontend */
class Backend : public QObject
{
    Q_OBJECT

    // Properties for accessing to current doctor's data from QML
    Q_PROPERTY(QString currentDoctorFullName READ getCurrentDoctorFullName)
    Q_PROPERTY(QString currentDoctorSpecialization READ getCurrentDoctorSpecialization)
    Q_PROPERTY(QString currentDoctorInstitutionName READ getCurrentDoctorInstitutionName)
    Q_PROPERTY(QString currentDoctorInstitutionCode READ getCurrentDoctorInstitutionCode)
    Q_PROPERTY(QString currentDoctorInstitutionAddress READ getCurrentDoctorInstitutionAddress)
    Q_PROPERTY(QString currentDoctorInn READ getCurrentDoctorInn)
    Q_PROPERTY(QString currentDoctorLicenseInfo READ getCurrentDoctorLicenseInfo)
    Q_PROPERTY(QString currentDoctorInitials READ getCurrentDoctorInitials)

    Q_PROPERTY(bool isDoctorDbEmpty READ getIsDoctorDbExists)

public:
    explicit Backend(QObject *parent = nullptr);

    /*! Global class for accessing the doctor's database */
    DoctorDataBase doctorDb;

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
    void changeDoctorProfile();

public slots:
    void addNewDoctorProfile(QString doctorFullName, QString doctorSpecialization,
                             QString doctorInstitutionName, QString doctorInstitutionCode,
                             QString doctorInstitutionAddress, QString doctorInn,
                             QString doctorLicenseInfo);

    void setCurrentDoctorInn(QString inn);
};

#endif // BACKEND_H
