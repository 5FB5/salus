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
#include <QObject>

class Doctor
{

public:
    Doctor();

    QString fullName;
    QString specialization;
    QString institutionName;
    QString institutionCode;
    QString institutionAddress;
    QString inn;
    QString licenseInfo;

    QString getProfileShortName(); // для инициалов
    QString findDiagnosis(QJsonArray diagnosesData);

    void createNewProfile(QString fullName, QString specialization,
                          QString institutionName, QString institutionCode, QString institutionAddress,
                          QString inn, QString licenseInfo);

    void selectProfile(QString profileName);
    void updateProfile(QString fullname, QString key, QString value);
    void addDiagnosis(QString fullname, QString value);
    void editDiagnosis(QJsonArray diagnosesData, QString key, QString value);

    QJsonDocument loadJson();

    QJsonArray diagnosesData;

private:
    QString getProfileField(QString fullname, QString key);

    bool isProfileExists(QString fullname);
    bool isDiagnosisExists(QJsonArray data, QString value);

    void saveProfileToJson(QJsonArray array);
};

#endif // DOCTOR_H
