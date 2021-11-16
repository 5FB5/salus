#ifndef PATIENTDB_H
#define PATIENTDB_H

#include "patient.h"
#define JSON_PATIENT_FILE_PATH QCoreApplication::applicationDirPath() + "/patients.json"
#include <QCoreApplication>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


class patientDB : public QObject
{
    Q_OBJECT

public:

    explicit patientDB(QObject *parent = nullptr);

    QList<Patient>* patientList = nullptr;


//    QString getShortName();

//    QJsonDocument getPatientData();

    QJsonDocument loadJson();
public slots:
    void addNewPatient(  QString fullName, quint8 age,
                         bool sex,
                         QDate birthDate,
                         QString adress,
                         QString insuranceCompany,
                         QString insuranceNumber,
                         QString phoneNumber,
                         QString occupation,
                         QString diagnosis,
                         QList<QString> diseases,
                         QString diseaseDescription);

//    void updatePatient();

//    void deletePatient(QString insuranceNumber);
private:
    void getPatientListFromJson();
    bool isProfileExists(QString insuranceNumber);
    QJsonArray convertListToJsonArray(const QList<QString> &list);
    bool saveProfileToJson(Patient patientProfile);


};

#endif // PATIENTDB_H
