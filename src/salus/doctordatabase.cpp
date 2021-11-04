#include "doctordatabase.h"

DoctorDataBase::DoctorDataBase(QObject *parent) : QObject(parent)
{
    getDoctorsListFromJson();
}

void DoctorDataBase::createNewProfile(QString fullName, QString specialization,
                                      QString institutionName, QString institutionCode, QString institutionAddress,
                                      QString inn, QString licenseInfo)
{

    // Пример структуры
    //    [
    //        {
    //            "diagnoses": [        // Набор собственных наименований диагнозов для подстановки в карту пациента
    //                "Кариес",
    //                "Пульпит"
    //            ],
    //            "fullname": "Иванов Иван Иванович",
    //            "inn": "0000000",
    //            "institutionAddress": "ул. Строителей, д 25, кв. 12",
    //            "institutionCode": "11111111",
    //            "institutionName": "ИП Иванов И.И.",
    //            "licenseInfo": "Лицензия №256",
    //            "specialization": "Стоматолог"
    //            "treatments": [       // Набор собственных наименований способов лечения
    //                "Антисептик"
    //            ]
    //        }
    //    ]

    if (doctorsList == nullptr) {
        doctorsList = new QList<Doctor>;
    }
    else {
        if (isProfileExists(inn) == true) {
            qDebug() << "Salus: [DoctorDataBase.h] createNewProfile() - Profile " << fullName << " already exists. Selecting this profile...\n";
            return;
        }
    }

    Doctor newDoctor;

    // Заполняем данными из введённых полей
    newDoctor.fullName = fullName;
    newDoctor.specialization = specialization;
    newDoctor.institutionName = institutionName;
    newDoctor.institutionCode = institutionCode;
    newDoctor.institutionAddress = institutionAddress;
    newDoctor.inn = inn;
    newDoctor.licenseInfo = licenseInfo;

    doctorsList->append(newDoctor);

    qDebug() << "Salus: [DoctorDataBase.h] createNewProfile() - Saving new profile...\n";
    saveProfileToJson(newDoctor);
}

QJsonDocument DoctorDataBase::loadJson()
{
    QFileInfo fInfo(JSON_DOCTOR_FILE_PATH);
    QFile f(JSON_DOCTOR_FILE_PATH);

    if (fInfo.exists()) {
        f.open(QFile::ReadOnly);
        QJsonDocument jd = QJsonDocument::fromJson(f.readAll());
        f.close();
        return jd;
    }
    else {
        f.open(QFile::WriteOnly);
        QJsonDocument jd;
        f.write(jd.toJson());
        f.close();
        return jd;
    }
}

QJsonArray DoctorDataBase::convertListToJsonArray(const QList<QString> &list)
{
    QJsonArray array;

    for (auto &data : list) {
        array.append(data);
    }

    return array;
}

//void DoctorDataBase::addDiagnosis(QString value)
//{
//    QJsonDocument doc = loadJson();
//    QJsonArray array = doc.array(), currentObjDiagnoses;
//    QJsonObject currentObj;

//    for (int i = 0; i < array.size(); ++i) {
//        for (auto j = array.cbegin(); j < array.cend(); ++j) {
//            currentObj = j->toObject();

//            if (currentObj["fullname"] == this->fullName) {
//                currentObjDiagnoses = currentObj["diagnoses"].toArray();

//                if (isArrayItemExists(currentObjDiagnoses, value) == false) {
//                    currentObjDiagnoses.append(value);
//                    currentObj["diagnoses"] = currentObjDiagnoses;

//                    array.replace(i, currentObj);

//                    qDebug() << "Salus: [DoctorDataBase.h] addDiagnosis() - Saving new diagnosis...\n";
//                    saveProfileToJson(array);
//                    break;
//                }
//                else {
//                    qDebug() << "Salus: [DoctorDataBase.h] addDiagnosis() - Diagnosis " << value << " already exists\n";
//                }
//            }
//        }
//    }
//}

//void DoctorDataBase::addTreatment(QString value)
//{
//    QJsonDocument doc = loadJson();
//    QJsonArray array = doc.array(), currentObjTreatments;
//    QJsonObject currentObj;

//    for (int i = 0; i < array.size(); ++i) {
//        for (auto j = array.cbegin(); j < array.cend(); ++j) {
//            currentObj = j->toObject();

//            if (currentObj["fullname"] == this->fullName) {
//                currentObjTreatments = currentObj["treatments"].toArray();

//                if (isArrayItemExists(currentObjTreatments, value) == false) {
//                    currentObjTreatments.append(value);
//                    currentObj["treatments"] = currentObjTreatments;

//                    array.replace(i, currentObj);

//                    qDebug() << "Salus: [DoctorDataBase.h] addTreatments() - Saving new treatment...\n";
//                    saveProfileToJson(array);
//                    break;
//                }
//                else {
//                    qDebug() << "Salus: [DoctorDataBase.h] addTreatments() - Treatment " << value << " already exists\n";
//                }
//            }
//        }
//    }
//}

void DoctorDataBase::getDoctorsListFromJson()
{
    QJsonDocument doc = loadJson();

    if (doc.isEmpty() == true) {
        return;
    }

    doctorsList = new QList<Doctor>;

    Doctor currentProfile;

    QJsonArray array = doc.array(), currentObjDiagnoses, currentObjTreatments;
    QJsonObject currentObj;

    foreach(const QJsonValue &v, array) {

        currentObj = v.toObject();

        currentProfile.fullName = currentObj["fullname"].toString();
        currentProfile.specialization = currentObj["specialization"].toString();
        currentProfile.institutionName = currentObj["institutionName"].toString();
        currentProfile.institutionCode = currentObj["institutionCode"].toString();
        currentProfile.institutionAddress = currentObj["institutionAddress"].toString();
        currentProfile.licenseInfo = currentObj["licenseInfo"].toString();
        currentProfile.inn = currentObj["inn"].toString();

        currentObjDiagnoses = currentObj["diagnoses"].toArray();
        currentObjTreatments = currentObj["treatments"].toArray();

        foreach(QJsonValue v, currentObjDiagnoses) {
            currentProfile.diagnoses.append(v.toString());
        }

        foreach(QJsonValue v, currentObjTreatments) {
            currentProfile.treatments.append(v.toString());
        }

        doctorsList->append(currentProfile);
    }
}

// TODO: make diagnoses array editable
//void DoctorDataBase::editDiagnosis(QJsonArray diagnosesData, QString value)
//{

//}

void DoctorDataBase::saveProfileToJson(Doctor doctorProfile)
{
    QJsonDocument jsonDocument = loadJson();
    QJsonArray jsonArray = jsonDocument.array(), doctorProfileDiagnoses, doctorProfileTreatments;
    QJsonObject DoctorProfileObj;

    doctorProfileDiagnoses = convertListToJsonArray(doctorProfile.diagnoses);
    doctorProfileDiagnoses = convertListToJsonArray(doctorProfile.treatments);

    DoctorProfileObj.insert("fullname", doctorProfile.fullName);
    DoctorProfileObj.insert("specialization", doctorProfile.specialization);
    DoctorProfileObj.insert("institutionName", doctorProfile.institutionName);
    DoctorProfileObj.insert("institutionCode", doctorProfile.institutionCode);
    DoctorProfileObj.insert("institutionAddress", doctorProfile.institutionAddress);
    DoctorProfileObj.insert("inn", doctorProfile.inn);
    DoctorProfileObj.insert("licenseInfo", doctorProfile.licenseInfo);

    DoctorProfileObj.insert("diagnoses", doctorProfileDiagnoses);
    DoctorProfileObj.insert("treatments", doctorProfileTreatments);

    jsonArray.append(DoctorProfileObj);

    jsonDocument.setArray(jsonArray);

    QFile jsonFile(JSON_DOCTOR_FILE_PATH);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(jsonDocument.toJson());
    jsonFile.close();

    qDebug() << "\tSalus: [DoctorDataBase.h] saveProfileToJson() - Profile saved\n";
}

//QJsonArray DoctorDataBase::getArray(QString profileName, QString key)
//{
//    QJsonDocument doc = loadJson();
//    QJsonArray array = doc.array(), objArray;
//    QJsonObject obj;

//    if (isProfileExists(profileName) == true) {
//        foreach(const QJsonValue &v, array) {
//            obj = v.toObject();

//            if (obj["fullname"] == profileName) {
//                objArray = obj[key].toArray();
//                //qDebug() << "Salus: [DoctorDataBase.h] getArray() - Array '" << key << "' from profile '" << profileName << "' is " << objArray << "\n";
//            }
//        }
//    }
//    else {
//        qDebug() << "Salus: [DoctorDataBase.h] getArray() - Can't get an array from non-existing profile " << profileName << "\n";
//    }

//    return objArray;
//}

//void DoctorDataBase::selectProfile(QString profileName)
//{
//    if (isProfileExists(profileName) == true) {
//        this->fullName = getProfileField(profileName, "fullname");
//        this->specialization = getProfileField(profileName, "specialization");
//        this->institutionName = getProfileField(profileName, "institutionName");
//        this->institutionAddress = getProfileField(profileName, "institutionAddress");
//        this->institutionCode = getProfileField(profileName, "institutionCode");
//        this->inn = getProfileField(profileName, "inn");
//        this->licenseInfo = getProfileField(profileName, "licenseInfo");
//        this->diagnosesData = getArray(profileName, "diagnoses");
//        this->treatmentsData = getArray(profileName, "treatments");

//        qDebug() << "Salus: [DoctorDataBase.h] selectProfile() - Profile " << profileName << " selected\n";
//    }
//    else {
//        qDebug() << "Salus: [DoctorDataBase.h] selectProfile() - can't select non-existing profile (" << profileName << ")\n";
//        return;
//    }
//}

//void DoctorDataBase::updateProfile(QString key, QString value)
//{
//    QJsonDocument doc = loadJson();
//    QJsonArray array = doc.array();
//    QJsonObject currentObj;

//    for (int i = 0; i < array.size(); ++i) {
//        for (auto j = array.cbegin(); j < array.cend(); ++j) {
//            currentObj = j->toObject();

//            if ((currentObj["fullname"] == this->fullName)) {
//                if (currentObj[key] == value) {
//                    qDebug() << "Salus: [DoctorDataBase.h] updateProfile() - value " << value << " is equal to profile's value (" << currentObj[key].toString() << ")\n";
//                    return;
//                }
//                currentObj[key] = value;
//                array.replace(i, currentObj);

//                qDebug() << "Salus: [DoctorDataBase.h] updateProfile() - Saving updated key...\n";
//                saveProfileToJson(array);

//                qDebug() << "Salus: [DoctorDataBase.h] updateProfile() - object's info (" << key << ") updated\n";
//            }
//        }
//    }
//}

//QString DoctorDataBase::getProfileField(QString fullname, QString key)
//{
//    QJsonDocument doc = loadJson();
//    QJsonArray array = doc.array();
//    QString field;

//    foreach (const QJsonValue &v, array) {
//        if (v["fullname"] == fullname) {
//            field = v[key].toString();
//        }
//        else if (v["fullname"] != fullname) {
//            continue;
//        }
//        else {
//            qDebug() << "Salus: [DoctorDataBase.h] getProfileField() - Can't take a field from non-existing profile (" << fullName << ")\n";
//            break;
//        }

//    }

//    return !field.isEmpty() ? field : nullptr;
//}

//QString DoctorDataBase::getProfileShortName()
//{
//    QString shortName;

//    if (isProfileExists(this->fullName) == true) {
//        QString firstName;
//        QString lastNameLetter;
//        QString middleNameLetter;

//        QString fullname = getProfileField(this->fullName, "fullname");
//        QStringList sl = fullname.split(' ', Qt::SkipEmptyParts);

//        firstName = sl[0];
//        lastNameLetter = sl[1].at(0);
//        middleNameLetter = sl[2].at(0);

//        shortName = lastNameLetter + '.' + middleNameLetter + "." + firstName;

//    }
//    else {
//        qDebug() << "Salus: [DoctorDataBase.h] getProfileShortName() - Can't get name from non-existing profile (" << this->fullName << ")\n";
//    }

//    return !shortName.isEmpty() ? shortName : nullptr;
//}

bool DoctorDataBase::isProfileExists(QString inn)
{
    for(Doctor currentDoctor : *doctorsList) {
        if (currentDoctor.inn == inn) {
            return true;
        }
    }

    return false;

    //return getProfileField(inn, "inn") == inn ? true : false;
}

//bool DoctorDataBase::isArrayItemExists(QJsonArray data, QString value)
//{
//    bool isExists = false;
//    int i = 0;

//    while((i < data.size()) && (isExists == false)) {
//        isExists = (data[i] == value);
//        i++;
//    }
//    return isExists;
//}
