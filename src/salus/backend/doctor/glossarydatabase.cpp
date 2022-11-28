#include "glossarydatabase.h"

GlossaryDatabase::GlossaryDatabase()
{
    getDataListFromJson();
}

QJsonDocument GlossaryDatabase::loadJson()
{
    QFileInfo fInfo(JSON_GLOSSARY_FILE_PATH);
    QFile f(JSON_GLOSSARY_FILE_PATH);

    if (fInfo.exists() == false)
    {
        f.open(QFile::WriteOnly);
        QJsonDocument jd;

        fillDocumentDefaultData(jd);

        f.write(jd.toJson());
        f.close();
        return jd;
    }

    f.open(QFile::ReadOnly);
    QJsonDocument jd = QJsonDocument::fromJson(f.readAll());
    f.close();
    return jd;
}

void GlossaryDatabase::fillDocumentDefaultData(QJsonDocument &doc)
{
    QJsonObject obj;

    QList<QString> defaultDiagnosesList;
//    QList<QString> defaultTreatmentsList;

    defaultDiagnosesList.append("К02.0 — кариес эмали стадия белого (мелового) пятна (начальный кариес)");
    defaultDiagnosesList.append("К02.1 — кариес дентина");
    defaultDiagnosesList.append("К02.2 — кариес цемента");
    defaultDiagnosesList.append("К02.3 — приостановившийся кариес зубов");
    defaultDiagnosesList.append("К02.4 — одонтоклазия детская меланодентия, меланодонтоклазия");
    defaultDiagnosesList.append("К02.8 — другой уточнённый кариес зубов");
    defaultDiagnosesList.append("К02.9 — кариес зубов неуточненный");

    obj.insert("diagnoses", convertListToJsonArray(defaultDiagnosesList));

    doc.setObject(obj);
}

QJsonArray GlossaryDatabase::convertListToJsonArray(const QList<QString> &list)
{
    QJsonArray array;

    if (list.isEmpty() == true)
        return array;

    for (int i = 0; i < list.size(); i++)
    {
        QJsonValue item = static_cast<QJsonValue>(list[i]);
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

    QJsonArray array = doc.array();
    QJsonObject currentObj;

    if (array.isEmpty() == true)
        return;

    // Перебор диагнозов и терапии
    foreach (const QJsonValue &v, array)
    {
        currentObj = v.toObject();

        *diagnosesList = convertJsonArrayToList(currentObj["diagnoses"].toArray());
        *treatmentsList = convertJsonArrayToList(currentObj["treatments"].toArray());
    }
}

QList<QString> GlossaryDatabase::convertJsonArrayToList(const QJsonArray array)
{
    QList<QString> tmpArray;

    for (const auto &element : array)
        tmpArray.append(element.toString());

    return tmpArray;
}
