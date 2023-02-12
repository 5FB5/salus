#ifndef GLOSSARYDATABASE_H
#define GLOSSARYDATABASE_H

#define JSON_GLOSSARY_FILE_PATH QCoreApplication::applicationDirPath() + "/glossary.json"

#include <QCoreApplication>
#include <QFileInfo>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QObject>

class GlossaryDatabase : public QObject
{
    Q_OBJECT

private:    
    QList<QString> *diagnosesList = nullptr;
    QList<QString> *treatmentsList = nullptr; // терапия
    QList<QString> *symptomsList = nullptr;
    QList<QString> *userList = nullptr; // пользовательские формулировки

    QJsonDocument loadJson();

    QJsonArray convertListToJsonArray(const QList<QString> list);

    QList<QString> convertJsonArrayToList(const QJsonArray array);

    void getDataListFromJson();
    void fillDiagnosesField(QList<QString> *list);
    void fillDocumentDefaultData(QJsonDocument *doc);
    void saveDataToJson();

public:
    GlossaryDatabase();
    ~GlossaryDatabase();

    void addDataToDiagnosesList(QString data);
    void addDataToTreatmentsList(QString data);
    void addDataToSymptomsList(QString data);
    void addDataToUserList(QString data);

    void editDiagnosis(QString oldData, QString newData);
    void editTreatment(QString oldData, QString newData);
    void editSymptom(QString oldData, QString newData);
    void editUserListItem(QString oldData, QString newData);

    void deleteDiagnosis(QString data);
    void deleteTreatment(QString data);
    void deleteSymptom(QString data);
    void deleteUserListItem(QString data);

    QString getDiagnosisAt(int index);
    QString getTreatmentAt(int index);
    QString getSymptomAt(int index);
    QString getUserItemAt(int index);

    QStringList getDiagnosesListModel();
    QStringList getTreatmentsListModel();
    QStringList getSymptomsListModel();
    QStringList getUserListModel();

};

#endif // GLOSSARYDATABASE_H
