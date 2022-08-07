#ifndef PATIENTDATABASE_H
#define PATIENTDATABASE_H

#define JSON_PATIENT_FILE_PATH QCoreApplication::applicationDirPath() + "/patients.json"

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

#include "patient.h"
#include "patientcardrecord.h"

class PatientDataBase : public QObject
{
    Q_OBJECT

private:
    void getPatientsListFromJson();
    void saveProfileToJson(Patient patientProfile);

    QJsonDocument loadJson();

    QJsonArray convertListToJsonArray(const QList<QString> &list);
    QJsonArray convertRecordsToJsonArray(const QList<Record_t> &records);

    QList<Record_t> convertJsonRecordsToList(const QJsonArray recordsArray);

    bool isProfileExists(QString birthDate);

public:
    explicit PatientDataBase(QObject *parent = nullptr);

    QList<Patient>* patientsList = nullptr;

    void addNewPatient(QString fullName, quint16 age, bool sex,
                       QString birthDate, QString address,
                       QString phoneNumber, QString occupation);

    void addNewRecord(QString birthDate, QString recordDate, QString anamnesis, QString complaints,
                      QString diseases, QString diagnosis, QString treatment);

    void reloadDatabase();
    void updateDbToFile();

    bool deletePatient(QString birthDate);

    QString getFullName(QString birthDate);
    QString getBirthDate(QString birthDate); // FIXME: возможно оно должно возвращать QDate
    QString getAddress(QString birthDate);
    QString getOccupation(QString birthDate);
    QString getDiagnosis(QString birthDate);
    QString getAnamnesis(QString birthDate);
    QString getPhoneNumber(QString birthDate);

    bool getSex(QString birthDate);

    quint16 getAge(QString birthDate);

    QList<Record_t> getRecordsList(QString birthDate);

signals:
    void recordAdded();

//    QList<QString> getDiseasesList(QString birthDate);
//    QList<QString> getComplaintsList(QString birthDate);
    // QString getAnamnesis(QString insuranceNumber);

    // QString getPatientInitials(QString insuranceNumber);
};

#endif // PATIENTDATABASE_H
