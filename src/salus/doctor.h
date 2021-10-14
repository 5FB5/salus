#ifndef DOCTOR_H
#define DOCTOR_H

#define JSON_FILE_PATH QCoreApplication::applicationDirPath() + "/doctors.json"

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

    void createNewProfile(QString fullName, QString specialization,
                          QString institutionName, QString institutionCode, QString institutionAddress,
                          QString inn, QString licenseInfo);

    void loadProfileFromJson(QString doctorFullName);

    bool isProfileExists(QString fullname);

    QString getDoctorShortName(QString fullName); // для инициалов

private:
    void saveProfileToJson(QJsonArray jsonArray);
    QJsonDocument loadJson();

};

#endif // DOCTOR_H
