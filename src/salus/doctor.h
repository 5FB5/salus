#ifndef DOCTOR_H
#define DOCTOR_H

#define JSON_DOCTOR_FILE_PATH QCoreApplication::applicationDirPath() + "/doctors.json"

#include <QCoreApplication>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <QtQml/qqml.h>

class Doctor : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QString fullName READ fullName WRITE setFullName)
//    Q_PROPERTY(QString specialization READ specialization WRITE setspecialization)
//    Q_PROPERTY(QString inn READ inn WRITE setInn)
//    Q_PROPERTY(QString institutionName READ institutionName WRITE setInstitutionName)
//    Q_PROPERTY(QString institutionAddress READ institutionAddress WRITE setInstitutionAddress)
//    Q_PROPERTY(QString institutionCode READ institutionCode WRITE setInstitutionCode)
//    Q_PROPERTY(QString licenseInfo READ licenseInfo WRITE setlicenseInfo)
    QML_ELEMENT

public:
    explicit Doctor(QObject *parent = nullptr);

    QString fullName;
    void setFullName(const QString &fullName);

    QString specialization;
    QString institutionName;
    QString institutionCode;
    QString institutionAddress;
    QString inn;
    QString licenseInfo;

    /*! Returns short name (initials) of full name */
    QString getProfileShortName(); // для инициалов
    //QString findDiagnosis(QJsonArray diagnosesData);

    void createNewProfile(QString fullName, QString specialization,
                          QString institutionName, QString institutionCode, QString institutionAddress,
                          QString inn, QString licenseInfo);


    /*! Set profile fields for current instance of Doctor class */
    void selectProfile(QString profileName);
    /*! Update profile's data via JSON's key */
    void updateProfile(QString key, QString value);

    /*! Add custom diagnosis to doctor's database */
    void addDiagnosis(QString value);

    /*! Add custom treatment to doctor's database */
    void addTreatment(QString value);
    // TODO: void editTreatments...
    // TODO: void editDiagnosis(QJsonArray diagnosesData, QString key, QString value);

    /*! Returns doctors.json file data */
    QJsonDocument loadJson();

    QJsonArray diagnosesData; // массив для хранения собственных формулировок возможных диагнозов исходя из диагностики
    QJsonArray treatmentsData; // массив для хранения собственных формулировок возможных процедур лечения

private:
    /*! Returns JSON's value via key */
    QString getProfileField(QString fullname, QString key);

    /*! Returns true if profile is exists in doctors.json */
    bool isProfileExists(QString fullname);

    /*! Returns true if item from current array exists */
    bool isArrayItemExists(QJsonArray data, QString value);

    /*! Save doctor's profile data to doctors.json file */
    void saveProfileToJson(QJsonArray array);

    /*! Returns array from profile */
    QJsonArray getArray(QString profileName, QString key);
};

#endif // DOCTOR_H
