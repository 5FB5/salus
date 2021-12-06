#ifndef PATIENTDATABASE_H
#define PATIENTDATABASE_H

#define JSON_PATIENT_FILE_PATH QCoreApplication::applicationDirPath() + "/patients.json"

#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QList>
#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "patient.h"

class PatientDataBase : public QObject
{
    Q_OBJECT

public:

    explicit PatientDataBase(QObject *parent = nullptr);

    QList<Patient>* patientsList = nullptr;

    void addNewPatient(QString fullName, quint16 age, bool sex,
                       QString birthDate, QString address,
                       quint16 phoneNumber, QString occupation);

    void deletePatient(QString birthDate);

    QString getFullName(QString birthDate);
    QString getBirthDate(QString birthDate); // FIXME: возможно оно должно возвращать QDate
    QString getAddress(QString birthDate);
    QString getOccupation(QString birthDate);
    QString getDiagnosis(QString birthDate);
    QString getAnamnesis(QString birthDate);

    QList<QString> getDiseasesList(QString birthDate);
    QList<QString> getComplaintsList(QString birthDate);
    // QString getAnamnesis(QString insuranceNumber);

    // QString getPatientInitials(QString insuranceNumber);

    bool getSex(QString birthDate);

    quint16 getAge(QString birthDate);
    quint16 getPhoneNumber(QString birthDate);

private:
    void getPatientsListFromJson();
    void saveProfileToJson(Patient patientProfile);

    QJsonDocument loadJson();

    QJsonArray convertListToJsonArray(const QList<QString> &list);

    bool isProfileExists(QString birthDate);
};

#endif // PATIENTDATABASE_H
