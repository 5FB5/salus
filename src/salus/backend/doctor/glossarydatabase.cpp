#include "glossarydatabase.h"

GlossaryDatabase::GlossaryDatabase()
{
    getDataListFromJson();
}

GlossaryDatabase::~GlossaryDatabase()
{
    saveDataToJson();
}

void GlossaryDatabase::saveDataToJson()
{
    QJsonArray diagnoses = convertListToJsonArray(*diagnosesList);
    QJsonArray treatments = convertListToJsonArray(*treatmentsList);

    QJsonObject obj;
    QJsonDocument doc;

    QFile f(JSON_GLOSSARY_FILE_PATH);

    obj.insert("diagnoses", diagnoses);
    obj.insert("treatments", treatments);

    doc.setObject(obj);

    f.open(QFile::WriteOnly);
    f.write(doc.toJson());
    f.close();
}

void GlossaryDatabase::addDataToDiagnosesList(QString data)
{
    if (diagnosesList == nullptr)
        return;

    diagnosesList->append(data);
}

void GlossaryDatabase::addDataToTreatmentsList(QString data)
{
    if (treatmentsList == nullptr)
        return;

    treatmentsList->append(data);
}

QJsonDocument GlossaryDatabase::loadJson()
{
    QFileInfo fInfo(JSON_GLOSSARY_FILE_PATH);
    QFile f(JSON_GLOSSARY_FILE_PATH);

    if (fInfo.exists() == false)
    {
        f.open(QFile::WriteOnly);
        QJsonDocument jd;

        fillDocumentDefaultData(&jd);

        f.write(jd.toJson());
        f.close();
        return jd;
    }

    f.open(QFile::ReadOnly);
    QJsonDocument jd = QJsonDocument::fromJson(f.readAll());
    f.close();
    return jd;
}

void GlossaryDatabase::fillDocumentDefaultData(QJsonDocument *doc)
{
    QJsonObject obj;

    QList<QString> defaultDiagnosesList;
    QList<QString> defaultTreatmentsList;

    defaultDiagnosesList.append("К02.0 — кариес эмали стадия белого (мелового) пятна (начальный кариес)");
    defaultDiagnosesList.append("К02.1 — кариес дентина");
    defaultDiagnosesList.append("К02.2 — кариес цемента");
    defaultDiagnosesList.append("К02.3 — приостановившийся кариес зубов");
    defaultDiagnosesList.append("К02.4 — одонтоклазия детская меланодентия, меланодонтоклазия");
    defaultDiagnosesList.append("К02.8 — другой уточнённый кариес зубов");
    defaultDiagnosesList.append("К02.9 — кариес зубов неуточненный");

    obj.insert("diagnoses", convertListToJsonArray(defaultDiagnosesList));
    obj.insert("treatments", convertListToJsonArray(defaultTreatmentsList));

    doc->setObject(obj);
}

QJsonArray GlossaryDatabase::convertListToJsonArray(const QList<QString> list)
{
    QJsonArray array;

    if (list.isEmpty() == true)
        return array;

    for (int i = 0; i < list.size(); i++)
    {
        QJsonValue item = static_cast<QJsonValue>(list.at(i));
        array.insert(i, item);
    }

    return array;
}

void GlossaryDatabase::getDataListFromJson()
{
    QJsonDocument doc = loadJson();

    if (diagnosesList == nullptr && treatmentsList == nullptr)
    {
        diagnosesList = new QList<QString>;
        treatmentsList = new QList<QString>;
    }

    QJsonObject obj = doc.object();

    if (obj.isEmpty() == true)
        return;

    *diagnosesList = convertJsonArrayToList(obj["diagnoses"].toArray());
//        *treatmentsList = convertJsonArrayToList(currentObj["treatments"].toArray());
}

QList<QString> GlossaryDatabase::convertJsonArrayToList(const QJsonArray array)
{
    QList<QString> tmpArray;

    for (const auto &element : array)
        tmpArray.append(element.toString());

    return tmpArray;
}
