#ifndef DOCTORDATABASE_H
#define DOCTORDATABASE_H

#define JSON_DOCTOR_FILE_PATH QCoreApplication::applicationDirPath() + "/doctors.json"

#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QObject>
#include <QList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "doctor.h"

class DoctorDataBase : public QObject
{
    Q_OBJECT

public:
    explicit DoctorDataBase(QObject *parent = nullptr);

    QList<Doctor>* doctorsList = nullptr;

    /*! Returns true if profile creating was successfully */
    void createNewProfile(QString fullName, QString specialization,
                          QString institutionName, QString institutionCode, QString institutionAddress,
                          QString inn, QString licenseInfo);

    // We use inn as primary key to get right doctor's data
    /*! Returns full name from profile via inn */
    QString getFullName(QString inn);
    /*! Returns specialization from profile via inn */
    QString getSpecialization(QString inn);
    /*! Returns institution's name from profile via inn */
    QString getInstitutionName(QString inn);
    /*! Returns code of institution from profile via inn */
    QString getInstitutionCode(QString inn);
    /*! Returns institution's address from profile via inn */
    QString getInstitutionAddress(QString inn);
    /*! Returns profile's inn via inn */
    QString getInn(); // FIXME: works only for 1 profile
    /*! Returns license from profile via inn */
    QString getLicenseInfo(QString inn);
    /*! Returns initials of full name via inn */
    QString getProfileInitials(QString inn);

    //QString findDiagnosis(QJsonArray diagnosesData);


//    /*! Update profile's data via JSON's key */
//    void updateProfile(QString key, QString value);

//    /*! Add custom diagnosis to doctor's database */
//    void addDiagnosis(QString value);

//    /*! Add custom treatment to doctor's database */
//    void addTreatment(QString value);
//    // TODO: void editTreatments...
//    // TODO: void editDiagnosis(QJsonArray diagnosesData, QString key, QString value);

private:
    void getDoctorsListFromJson();

    /*! Returns doctors.json file data */
    QJsonDocument loadJson();

    QJsonArray convertListToJsonArray(const QList<QString> &list);

//    /*! Returns JSON's value via key */
//    QString getProfileField(QString fullname, QString key);

    /*! Returns true if profile is exists in doctors.json */
    bool isProfileExists(QString inn);

//    /*! Returns true if item from current array exists */
//    bool isArrayItemExists(QJsonArray data, QString value);

    /*! Save doctor's profile data to doctors.json file */
    void saveProfileToJson(Doctor doctorProfile);

//    /*! Returns array from profile */
//    QJsonArray getArray(QString profileName, QString key);

};

#endif // DOCTORDATABASE_H
