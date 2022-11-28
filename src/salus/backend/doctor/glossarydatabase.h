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
    QList<QString> *treatmentsList = nullptr;

    QJsonDocument loadJson();

    QJsonArray convertListToJsonArray(const QList<QString> list);

    QList<QString> convertJsonArrayToList(const QJsonArray array);

    void getDataListFromJson();
    void fillDocumentDefaultData(QJsonDocument *doc);
    void saveDataToJson();

public:
    GlossaryDatabase();
    ~GlossaryDatabase();

    void addDataToDiagnosesList(QString data);
    void addDataToTreatmentsList(QString data);

    QStringList getDiagnosesListModel();

};

#endif // GLOSSARYDATABASE_H
