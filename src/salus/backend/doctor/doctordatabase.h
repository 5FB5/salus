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


    //QString findDiagnosis(QJsonArray diagnosesData);


//    /*! Update profile's data via JSON's key */
//    void updateProfile(QString key, QString value);

//    /*! Add custom diagnosis to doctor's database */
//    void addDiagnosis(QString value);

//    /*! Add custom treatment to doctor's database */
//    void addTreatment(QString value);

// TODO: void editTreatments...
// TODO: void editDiagnosis(QJsonArray diagnosesData, QString key, QString value);

private:
    void getDoctorsListFromJson();

    QJsonDocument loadJson();

    QJsonArray convertListToJsonArray(const QList<QString> &list);

    /*! Возвращает true, если профиль существует в файле doctors.json */
    bool isProfileExists(quint16 inn);

    /*! Сохраняет профиль в файл doctors.json */
    void saveProfileToJson(Doctor doctorProfile);

};

#endif // DOCTORDATABASE_H
