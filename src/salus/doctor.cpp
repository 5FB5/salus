#include "doctor.h"

Doctor::Doctor()
{

}

//void Doctor::createNewProfile(QString fullName, QString specialization,
//                              QString institutionName, QString institutionCode, QString institutionAddress,
//                              QString inn, QString licenseInfo)
//{

//    // Пример структуры
//    //    [
//    //        {
//    //            "diagnoses": [        // Набор собственных наименований диагнозов для подстановки в карту пациента
//    //                "Кариес",
//    //                "Пульпит"
//    //            ],
//    //            "fullname": "Иванов Иван Иванович",
//    //            "inn": "0000000",
//    //            "institutionAddress": "ул. Строителей, д 25, кв. 12",
//    //            "institutionCode": "11111111",
//    //            "institutionName": "ИП Иванов И.И.",
//    //            "licenseInfo": "Лицензия №256",
//    //            "specialization": "Стоматолог"
//    //            "treatments": [       // Набор собственных наименований способов лечения
//    //                "Антисептик"
//    //            ]
//    //        }
//    //    ]

//   if (isProfileExists(fullName) == true) {
//        qDebug() << "Salus: [Doctor.h] createNewProfile() - Profile " << fullName << " already exists. Selecting this profile...\n";
//        selectProfile(fullName);
//        return;
//    }

//    QJsonDocument jsonDocument = loadJson();

//    QJsonArray jsonArray = jsonDocument.array();
//    // объект для добавления данных нового пользователя в структуру
//    QJsonObject doctorProfileObj;

//    doctorProfileObj.insert("fullname", fullName);
//    doctorProfileObj.insert("specialization", specialization);
//    doctorProfileObj.insert("institutionName", institutionName);
//    doctorProfileObj.insert("institutionCode", institutionCode);
//    doctorProfileObj.insert("institutionAddress", institutionAddress);
//    doctorProfileObj.insert("inn", inn);
//    doctorProfileObj.insert("licenseInfo", licenseInfo);
//    doctorProfileObj.insert("diagnoses", diagnosesData);
//    doctorProfileObj.insert("treatments", treatmentsData);

//    jsonArray.append(doctorProfileObj);

//    qDebug() << "Salus: [Doctor.h] createNewProfile() - Saving new profile...\n";
//    saveProfileToJson(jsonArray);

//    // Сразу после добавления выбираем профиль
//    selectProfile(fullName);
//}

//QJsonDocument Doctor::loadJson()
//{
//    QFileInfo fInfo(JSON_DOCTOR_FILE_PATH);
//    QFile f(JSON_DOCTOR_FILE_PATH);

//    if (fInfo.exists()) {
//        f.open(QFile::ReadOnly);
//        QJsonDocument jd = QJsonDocument::fromJson(f.readAll());
//        f.close();
//        return jd;
//    }
//    else {
//        f.open(QFile::WriteOnly);
//        QJsonDocument jd;
//        f.write(jd.toJson());
//        f.close();
//        return jd;
//    }
//}

//void Doctor::addDiagnosis(QString value)
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

//                    qDebug() << "Salus: [Doctor.h] addDiagnosis() - Saving new diagnosis...\n";
//                    saveProfileToJson(array);
//                    break;
//                }
//                else {
//                    qDebug() << "Salus: [Doctor.h] addDiagnosis() - Diagnosis " << value << " already exists\n";
//                }
//            }
//        }
//    }
//}

//void Doctor::addTreatment(QString value)
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

//                    qDebug() << "Salus: [Doctor.h] addTreatments() - Saving new treatment...\n";
//                    saveProfileToJson(array);
//                    break;
//                }
//                else {
//                    qDebug() << "Salus: [Doctor.h] addTreatments() - Treatment " << value << " already exists\n";
//                }
//            }
//        }
//    }
//}

//// TODO: make diagnoses array editable
////void Doctor::editDiagnosis(QJsonArray diagnosesData, QString value)
////{

////}

//void Doctor::saveProfileToJson(QJsonArray array)
//{
//    QJsonDocument doc;
//    doc.setArray(array);

//    QFile jsonFile(JSON_DOCTOR_FILE_PATH);
//    jsonFile.open(QFile::WriteOnly);
//    jsonFile.write(doc.toJson());
//    jsonFile.close();

//    qDebug() << "\tSalus: [Doctor.h] saveProfileToJson() - Profile saved\n";
//}

//QJsonArray Doctor::getArray(QString profileName, QString key)
//{
//    QJsonDocument doc = loadJson();
//    QJsonArray array = doc.array(), objArray;
//    QJsonObject obj;

//    if (isProfileExists(profileName) == true) {
//        foreach(const QJsonValue &v, array) {
//            obj = v.toObject();

//            if (obj["fullname"] == profileName) {
//                objArray = obj[key].toArray();
//                //qDebug() << "Salus: [Doctor.h] getArray() - Array '" << key << "' from profile '" << profileName << "' is " << objArray << "\n";
//            }
//        }
//    }
//    else {
//        qDebug() << "Salus: [Doctor.h] getArray() - Can't get an array from non-existing profile " << profileName << "\n";
//    }

//    return objArray;
//}

//void Doctor::selectProfile(QString profileName)
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

//        qDebug() << "Salus: [Doctor.h] selectProfile() - Profile " << profileName << " selected\n";
//    }
//    else {
//        qDebug() << "Salus: [Doctor.h] selectProfile() - can't select non-existing profile (" << profileName << ")\n";
//        return;
//    }
//}

//void Doctor::updateProfile(QString key, QString value)
//{
//    QJsonDocument doc = loadJson();
//    QJsonArray array = doc.array();
//    QJsonObject currentObj;

//    for (int i = 0; i < array.size(); ++i) {
//        for (auto j = array.cbegin(); j < array.cend(); ++j) {
//            currentObj = j->toObject();

//            if ((currentObj["fullname"] == this->fullName)) {
//                if (currentObj[key] == value) {
//                    qDebug() << "Salus: [Doctor.h] updateProfile() - value " << value << " is equal to profile's value (" << currentObj[key].toString() << ")\n";
//                    return;
//                }
//                currentObj[key] = value;
//                array.replace(i, currentObj);

//                qDebug() << "Salus: [Doctor.h] updateProfile() - Saving updated key...\n";
//                saveProfileToJson(array);

//                qDebug() << "Salus: [Doctor.h] updateProfile() - object's info (" << key << ") updated\n";
//            }
//        }
//    }
//}

//QString Doctor::getProfileField(QString fullname, QString key)
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
//            qDebug() << "Salus: [Doctor.h] getProfileField() - Can't take a field from non-existing profile (" << fullName << ")\n";
//            break;
//        }

//    }

//    return !field.isEmpty() ? field : nullptr;
//}

//QString Doctor::getProfileShortName()
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
//        qDebug() << "Salus: [Doctor.h] getProfileShortName() - Can't get name from non-existing profile (" << this->fullName << ")\n";
//    }

//    return !shortName.isEmpty() ? shortName : nullptr;
//}

//bool Doctor::isProfileExists(QString fullname)
//{
//    return getProfileField(fullname, "fullname") == fullname ? true : false;
//}

//bool Doctor::isArrayItemExists(QJsonArray data, QString value)
//{
//    bool isExists = false;
//    int i = 0;

//    while((i < data.size()) && (isExists == false)) {
//        isExists = (data[i] == value);
//        i++;
//    }
//    return isExists;
//}
