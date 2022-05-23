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

    // We use inn as primary key to get right doctor's data
    /*! Возвращается ФИО врача через ИНН */
    QString getFullName(quint16 inn);
    /*! Возвращает наименование специализации врача через ИНН */
    QString getSpecialization(quint16 inn);
    /*! Возвращает наименование организации через ИНН */
    QString getInstitutionName(quint16 inn);
    /*! Возвращает код организации через ИНН */
    quint16 getInstitutionCode(quint16 inn);
    /*! Возвращает адрес организации через ИНН */
    QString getInstitutionAddress(quint16 inn);
    /*! Возвращает ИНН врача */
    quint16 getInn(); // FIXME: works only for 1 profile
    /*! Возвращает наименование лицензии через ИНН */
    QString getLicenseInfo(quint16 inn);
    /*! Возвращает инициалы врача через ИНН */
    QString getProfileInitials(quint16 inn);

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

    /*! Возвращает данные из doctors.json */
    QJsonDocument loadJson();

    QJsonArray convertListToJsonArray(const QList<QString> &list);

    /*! Возвращает true, если профиль существует в файле doctors.json */
    bool isProfileExists(quint16 inn);

    /*! Сохраняет профиль в файл doctors.json */
    void saveProfileToJson(Doctor doctorProfile);

};

#endif // DOCTORDATABASE_H
