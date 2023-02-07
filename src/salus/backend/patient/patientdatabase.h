#ifndef PATIENTDATABASE_H
#define PATIENTDATABASE_H

#define JSON_PATIENT_FILE_PATH QCoreApplication::applicationDirPath() + "/patients.json"

#include <QCoreApplication>
#include <QtWebEngineWidgets/QWebEngineView>
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
#include "PDFWriter/PDFWriter.h"

class PatientDataBase : public QObject
{
    Q_OBJECT

    enum PrintMode : int
    {
        ALL_CARD, // Карта целиком
        PAGE_ONLY, // Указанная страница
        RECORD // Дневник по записи
    };

private:
    void getPatientsListFromJson();
    void fillAnamnesis(Record_t recIt, QString *html);
    void fillComplaints(Record_t recIt, QString *html);
    void generateDiary(QString birthDate, std::vector<std::string> *paths);
    void generateFullCard(QString birthDate, QString path);
    void saveProfileToJson(Patient patientProfile);

    std::vector<std::string> paths;

    QEventLoop loop;
    QWebEngineView *webView;

    QJsonDocument loadJson();

    QJsonArray convertListToJsonArray(const QList<QString> &list);
    QJsonArray convertRecordsToJsonArray(const QList<Record_t> &records);

    QList<Record_t> convertJsonRecordsToList(const QJsonArray recordsArray);

    bool isProfileExists(QString birthDate);

public:
    explicit PatientDataBase(QObject *parent = nullptr);
    ~PatientDataBase();

    QList<Patient>* patientsList = nullptr;

    void addNewPatient(QString fullName, int age, bool sex,
                       QString birthDate, QString address,
                       QString phoneNumber, QString occupation);

    bool addNewRecord(QString birthDate, QString recordDate, QString anamnesis, QString complaints,
                      QString diseases, QString diagnosis, QString treatment, QString treatmentResult);

    void reloadDatabase();
    void updateDbToFile();
    void updateRecord(QString birthDate, QString recordDate, QString anamnesis,
                      QString complaints, QString diseases, QString diagnosis, QString treatment, QString treatmentResult);

    void deleteRecord(QString birthDate, QString recordDate);

    bool deletePatient(QString birthDate);

    QString getFullName(QString birthDate);
    QString getBirthDate(QString birthDate);
    QString getAddress(QString birthDate);
    QString getPhoneNumber(QString birthDate);
    QString getOccupation(QString birthDate);

    bool getSex(QString birthDate);

    int getAge(QString birthDate);

    QStringList getRecordsList(QString birthDate);

    QString getAnamnesis(QString birthDate, QString recordDate);
    QString getComplaints(QString birthDate, QString recordDate);
    QString getDiagnosis(QString birthDate, QString recordDate);
    QString getDiseases(QString birthDate, QString recordDate);
    QString getTreatment(QString birthDate, QString recordDate);
    QString getTreatmentResult(QString birthDate, QString recordDate);

    void saveCardPdf(QString birthDate, int opMode);

signals:
    void recordAdded();
};

#endif // PATIENTDATABASE_H
