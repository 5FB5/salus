#ifndef DOCTORDATABASE_H
#define DOCTORDATABASE_H

#define JSON_DOCTOR_FILE_PATH QCoreApplication::applicationDirPath() + "/doctors.json"

#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QList>
#include <QObject>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "doctor.h"

class DoctorDataBase : public QObject
{
    Q_OBJECT

private:
    void getDoctorsListFromJson();

    QString generateInitials(QString fullName);
    QJsonDocument loadJson();
    QJsonArray convertListToJsonArray(const QList<QString> &list);

    /*! Возвращает true, если профиль существует в файле doctors.json */
    bool isProfileExists(quint16 inn);

    /*! Сохраняет профиль в файл doctors.json */
    void saveProfileToJson(Doctor doctorProfile);

public:
    explicit DoctorDataBase(QObject *parent = nullptr);

    QList<Doctor>* doctorsList = nullptr;

    void createNewProfile(QString fullName, QString specialization,
                          QString institutionName, quint16 institutionCode, QString institutionAddress,
                          quint16 inn, QString licenseInfo);

    QString getFullName(quint16 inn);
    QString getSpecialization(quint16 inn);
    QString getInstitutionName(quint16 inn);
    QString getInstitutionAddress(quint16 inn);
    QString getLicenseInfo(quint16 inn);
    QString getProfileInitials(quint16 inn);

    quint16 getInstitutionCode(quint16 inn);
    quint16 getInn(); // FIXME: works only for 1 profile


//    /*! Update profile's data via JSON's key */
//    void updateProfile(QString key, QString value);



};

#endif // DOCTORDATABASE_H
