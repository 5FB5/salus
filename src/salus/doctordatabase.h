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

//    /*! Set profile fields for current instance of Doctor class */
//    void selectProfile(QString profileName);

public slots:
//    /*! Returns short name (initials) of full name */
//    QString getProfileShortName(); // для инициалов
    //QString findDiagnosis(QJsonArray diagnosesData);

    /*! Returns true if profile creating was successfully */
    void createNewProfile(QString fullName, QString specialization,
                          QString institutionName, QString institutionCode, QString institutionAddress,
                          QString inn, QString licenseInfo);

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
