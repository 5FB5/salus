#include "doctor.h"

Doctor::Doctor()
{

}

void Doctor::createNewProfile(QString fullName, QString specialization,
                              QString institutionName, QString institutionCode, QString institutionAddress,
                              QString inn, QString licenseInfo)
{

    // Пример структуры

    //    [
    //        {
    //            "fullname": "A",
    //            "inn": "F",
    //            "institutionAddress": "E",
    //            "institutionCode": "D",
    //            "institutionName": "C",
    //            "licenseInfo": "G",
    //            "specialization": "B"
    //        },
    //        {
    //            "fullname": "Z",
    //            "inn": "M",
    //            "institutionAddress": "N",
    //            "institutionCode": "B",
    //            "institutionName": "V",
    //            "licenseInfo": "L",
    //            "specialization": "X"
    //        }
    //    ]


   if (isProfileExists(fullName) == true) {
        qDebug() << "Salus: [Doctor.h] Profile " << fullName << " already exists\n";
        return;
    }

    QJsonDocument jsonDocument = loadJson();

    QJsonArray jsonArray = jsonDocument.array();
    // объект для добавления данных нового пользователя в структуру
    QJsonObject doctorProfileObj;

    doctorProfileObj.insert("fullname", fullName);
    doctorProfileObj.insert("specialization", specialization);
    doctorProfileObj.insert("institutionName", institutionName);
    doctorProfileObj.insert("institutionCode", institutionCode);
    doctorProfileObj.insert("institutionAddress", institutionAddress);
    doctorProfileObj.insert("inn", inn);
    doctorProfileObj.insert("licenseInfo", licenseInfo);

    jsonArray.append(doctorProfileObj);

    saveProfileToJson(jsonArray);
}

QJsonDocument Doctor::loadJson()
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

void Doctor::saveProfileToJson(QJsonArray array)
{
    QJsonDocument doc;
    doc.setArray(array);

    QFile jsonFile(JSON_DOCTOR_FILE_PATH);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(doc.toJson());
    jsonFile.close();

    qDebug() << "Salus: [Doctor.h] saveProfileToJson() - object saved\n";
}

void Doctor::selectProfile(QString profileName)
{
    this->fullName = getProfileField(profileName, "fullname");
    this->specialization = getProfileField(profileName, "specialization");
    this->institutionName = getProfileField(profileName, "institutionName");
    this->institutionAddress = getProfileField(profileName, "institutionAddress");
    this->institutionCode = getProfileField(profileName, "institutionCode");
    this->inn = getProfileField(profileName, "inn");
    this->licenseInfo = getProfileField(profileName, "licenseInfo");
}

void Doctor::updateProfile(QString fullname, QString key, QString value)
{
    QJsonDocument doc = loadJson();
    QJsonArray array = doc.array();
    QJsonObject currentObj;

    for (int i = 0; i < array.size(); ++i) {
        for (auto j = array.cbegin(); j < array.cend(); ++j) {
            currentObj = j->toObject();

            if (currentObj["fullname"] == fullname) {
                currentObj[key] = value;
                array.replace(i, currentObj);
                saveProfileToJson(array);
                qDebug() << "Salus: [Doctor.h] updateProfile() - object's info (" << key << ") updated\n";
                break;
            }
        }
    }
}

QString Doctor::getProfileField(QString fullname, QString key)
{
    QJsonDocument doc = loadJson();
    QJsonArray array = doc.array();
    QString field;

    foreach (const QJsonValue &v, array) {
        QJsonObject currentObject =  v.toObject();
        if (v["fullname"] == fullname) {
            //qDebug() << "Salus: [Doctor.h] getDoctorProfileField() - Profile " << fullname << ", return key " << key << " = " << v[key].toString() << "\n";
            field = v[key].toString();
        }
        else if (v["fullname"] != fullname) {
            continue;
        }
        else {
            qDebug() << "Salus: [Doctor.h] getProfileField() - Can't take a field from non-existing profile (" << fullName << ")\n";
            break;
        }

    }

    return !field.isEmpty() ? field : nullptr;
}

bool Doctor::isProfileExists(QString fullname)
{
    return getProfileField(fullname, "fullname") == fullname ? true : false;
}

/*
QString Doctor::getProfileShortName(QString fullName)
{

}
*/
