#ifndef PATIENTDATABASE_H
#define PATIENTDATABASE_H

#define JSON_PATIENT_FILE_PATH QCoreApplication::applicationDirPath() + "/patients.json"

#include <QCoreApplication>
#include <QtGui/QTextDocument>
#include <QPrinter>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QList>
#include <QStringList>
#include <QObject>
#include <QString>
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

    bool addNewRecord(QString birthDate, QString recordDate, QString anamnesis, QString complaints,
                      QString diseases, QString diagnosis, QString treatment);

    void reloadDatabase();
    void updateDbToFile();
    void updateRecord(QString birthDate, QString recordDate, QString anamnesis,
                      QString complaints, QString diseases, QString diagnosis, QString treatment);

    void deleteRecord(QString birthDate, QString recordDate);

    bool deletePatient(QString birthDate);

    QString getFullName(QString birthDate);
    QString getBirthDate(QString birthDate);
    QString getAddress(QString birthDate);
    QString getPhoneNumber(QString birthDate);
    QString getOccupation(QString birthDate);

    bool getSex(QString birthDate);

    quint16 getAge(QString birthDate);

    QStringList getRecordsList(QString birthDate);

    QString getAnamnesis(QString birthDate, QString recordDate);
    QString getComplaints(QString birthDate, QString recordDate);
    QString getDiagnosis(QString birthDate, QString recordDate);
    QString getDiseases(QString birthDate, QString recordDate);
    QString getTreatment(QString birthDate, QString recordDate);

    void saveCardPdf(QString birthDate);

signals:
    void recordAdded();

//    QList<QString> getDiseasesList(QString birthDate);
//    QList<QString> getComplaintsList(QString birthDate);
    // QString getAnamnesis(QString insuranceNumber);

    // QString getPatientInitials(QString insuranceNumber);
};

#endif // PATIENTDATABASE_H
