#include "glossarydatabase.h"

GlossaryDatabase::GlossaryDatabase()
{
    getDataListFromJson();
}

GlossaryDatabase::~GlossaryDatabase()
{
    saveDataToJson();
}

void GlossaryDatabase::getDataListFromJson()
{
    QJsonDocument doc = loadJson();

    if (diagnosesList == nullptr && treatmentsList == nullptr && symptomsList == nullptr && userList == nullptr)
    {
        diagnosesList = new QList<QString>;
        treatmentsList = new QList<QString>;
        symptomsList = new QList<QString>;
        userList = new QList<QString>;
    }

    QJsonObject obj = doc.object();

    if (obj.isEmpty() == true)
        return;

    *diagnosesList = convertJsonArrayToList(obj["diagnoses"].toArray());
    *treatmentsList = convertJsonArrayToList(obj["treatments"].toArray());
    *symptomsList = convertJsonArrayToList(obj["symptoms"].toArray());
    *userList = convertJsonArrayToList(obj["user"].toArray());
}

void GlossaryDatabase::saveDataToJson()
{
    QJsonArray diagnoses = convertListToJsonArray(*diagnosesList);
    QJsonArray treatments = convertListToJsonArray(*treatmentsList);
    QJsonArray symptoms = convertListToJsonArray(*symptomsList);
    QJsonArray userFormulations = convertListToJsonArray(*userList);

    QJsonObject obj;
    QJsonDocument doc;

    QFile f(JSON_GLOSSARY_FILE_PATH);

    obj.insert("diagnoses", diagnoses);
    obj.insert("treatments", treatments);
    obj.insert("symptoms", symptoms);
    obj.insert("user", userFormulations);

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

void GlossaryDatabase::addDataToSymptomsList(QString data)
{
    if (symptomsList == nullptr)
        return;

    symptomsList->append(data);
}

void GlossaryDatabase::addDataToUserList(QString data)
{
    if (userList == nullptr)
        return;

    userList->append(data);
}

void GlossaryDatabase::editDiagnosis(QString oldData, QString newData)
{
    if (diagnosesList == nullptr)
        return;

    for (int i = 0; i < diagnosesList->size(); i++)
    {
        if ((*diagnosesList)[i] == oldData)
            (*diagnosesList)[i] = newData;
    }
}

void GlossaryDatabase::editTreatment(QString oldData, QString newData)
{
    if (treatmentsList == nullptr)
        return;

    for (int i = 0; i < treatmentsList->size(); i++)
    {
        if ((*treatmentsList)[i] == oldData)
            (*treatmentsList)[i] = newData;
    }
}

void GlossaryDatabase::editSymptom(QString oldData, QString newData)
{
    if (symptomsList == nullptr)
        return;

    for (int i = 0; i < symptomsList->size(); i++)
    {
        if ((*symptomsList)[i] == oldData)
            (*symptomsList)[i] = newData;
    }
}

void GlossaryDatabase::editUserListItem(QString oldData, QString newData)
{
    if (userList == nullptr)
        return;

    for (int i = 0; i < userList->size(); i++)
    {
        if ((*userList)[i] == oldData)
            (*userList)[i] = newData;
    }
}

void GlossaryDatabase::deleteDiagnosis(QString data)
{
    if (diagnosesList == nullptr)
        return;

    for (int i = 0; i < diagnosesList->size(); i++)
    {
        if (diagnosesList->at(i) == data)
            diagnosesList->removeAt(i);
    }
}

void GlossaryDatabase::deleteSymptom(QString data)
{
    if (symptomsList == nullptr)
        return;

    for (int i = 0; i < symptomsList->size(); i++)
    {
        if (symptomsList->at(i) == data)
            symptomsList->removeAt(i);
    }
}

void GlossaryDatabase::deleteUserListItem(QString data)
{
    if (userList == nullptr)
        return;

    for (int i = 0; i < userList->size(); i++)
    {
        if (userList->at(i) == data)
            userList->removeAt(i);
    }
}
void GlossaryDatabase::deleteTreatment(QString data)
{
    if (diagnosesList == nullptr)
        return;

    for (int i = 0; i < treatmentsList->size(); i++)
    {
        if (treatmentsList->at(i) == data)
            treatmentsList->removeAt(i);
    }
}

QString GlossaryDatabase::getDiagnosisAt(int index)
{
    if (diagnosesList == nullptr || diagnosesList->isEmpty() == true)
        return "";

    return diagnosesList->at(index);
}

QString GlossaryDatabase::getTreatmentAt(int index)
{
    if (treatmentsList == nullptr || treatmentsList->isEmpty() == true)
        return "";

    return treatmentsList->at(index);
}

QString GlossaryDatabase::getSymptomAt(int index)
{
    if (symptomsList == nullptr || symptomsList->isEmpty() == true)
        return "";

    return symptomsList->at(index);
}

QString GlossaryDatabase::getUserItemAt(int index)
{
    if (userList == nullptr || userList->isEmpty() == true)
        return "";

    return userList->at(index);
}

QStringList GlossaryDatabase::getDiagnosesListModel()
{
    QStringList list;

    if (diagnosesList->isEmpty() == true)
        return list;

    for (const auto &record : *diagnosesList)
        list.append(record);

    return list;
}

QStringList GlossaryDatabase::getTreatmentsListModel()
{
    QStringList list;

    if (treatmentsList->isEmpty() == true)
        return list;

    for (const auto &record : *treatmentsList)
        list.append(record);

    return list;
}

QStringList GlossaryDatabase::getSymptomsListModel()
{
    QStringList list;

    if (symptomsList->isEmpty() == true)
        return list;

    for (const auto &record : *symptomsList)
        list.append(record);

    return list;
}

QStringList GlossaryDatabase::getUserListModel()
{
    QStringList list;

    if (userList->isEmpty() == true)
        return list;

    for (const auto &record : *userList)
        list.append(record);

    return list;
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
    QList<QString> defaultSymptomsList;
    QList<QString> defaultUserList;

    defaultDiagnosesList.append("К02.0 — кариес эмали стадия белого (мелового) пятна (начальный кариес)");
    defaultDiagnosesList.append("К02.1 — кариес дентина");
    defaultDiagnosesList.append("К02.2 — кариес цемента");
    defaultDiagnosesList.append("К02.3 — приостановившийся кариес зубов");
    defaultDiagnosesList.append("К02.4 — одонтоклазия детская меланодентия, меланодонтоклазия");
    defaultDiagnosesList.append("К02.8 — другой уточнённый кариес зубов");
    defaultDiagnosesList.append("К02.9 — кариес зубов неуточненный");

    obj.insert("diagnoses", convertListToJsonArray(defaultDiagnosesList));
    obj.insert("treatments", convertListToJsonArray(defaultTreatmentsList));
    obj.insert("symptoms", convertListToJsonArray(defaultSymptomsList));
    obj.insert("user", convertListToJsonArray(defaultUserList));

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

QList<QString> GlossaryDatabase::convertJsonArrayToList(const QJsonArray array)
{
    QList<QString> tmpArray;

    for (const auto &element : array)
        tmpArray.append(element.toString());

    return tmpArray;
}
