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

    void createNewProfile(QString fullName, QString specialization,
                          QString institutionName, QString institutionCode, QString institutionAddress,
                          QString inn, QString licenseInfo);

    void saveProfileToJson(QJsonArray array);
    void selectProfile(QString profileName);
    void updateProfile(QString fullname, QString key, QString value);

    bool isProfileExists(QString fullname);

    QString getProfileField(QString fullname, QString key);
    QString getProfileShortName(); // для инициалов

    QJsonDocument loadJson();

};

#endif // DOCTOR_H
