#include "doctor.h"

Doctor::Doctor(QString fullName, QString specialization,
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


   /* if (isProfileExists(fullName) == false) {
        qDebug() << "Salus: [Doctor.h] profile '" + fullName + "' already exists\n";
        return;
    }
*/
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
    QFileInfo fInfo(JSON_FILE_PATH);

    if (fInfo.exists()) {
        QFile f(JSON_FILE_PATH);
        f.open(QFile::ReadOnly);
        QJsonDocument jd = QJsonDocument::fromJson(f.readAll());
        f.close();
        return jd;
    }
    else {
        QFile f(JSON_FILE_PATH);
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

    QFile jsonFile(JSON_FILE_PATH);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(doc.toJson());
    jsonFile.close();

    qDebug() << "Salus: [Doctor.h] saveProfileToJson() - object saved\n";
}

QString Doctor::getProfileField(QString fullname, QString key)
{
    QJsonDocument doc = loadJson();
    QJsonArray array = doc.array();
    QString field;

    foreach (const QJsonValue &v, array) {
        QJsonObject currentObject =  v.toObject();
        if (v["fullname"] == fullname) {
            qDebug() << "Salus: [Doctor.h] getDoctorProfileField() - Profile " << fullname << " key " << key << " = " << v[key].toString() << "\n";
            field = v[key].toString();
        }
        else if (v["fullname"] != fullname) {
            continue;
        }
        else {
            qDebug() << "Salus: [Doctor.h] getProfileField() - Profile doesn't exists\n";
            field = nullptr;
        }

    }

    return field;
}


//bool Doctor::isProfileExists(QString fullname)
//{
//    QFileInfo jsonFileInfo(JSON_FILE_PATH);
//    if (!jsonFileInfo.exists()) {
//        qDebug() << "Salus: [Doctor.h -> isProfileExists()] " + JSON_FILE_PATH + " not found\n";
//        return false;
//    }

//    /*
//     * открываем файл
//     * парсим всё содержимое
//     * берём оттуда данные
//     * смотрим наличие профиля
//     * если есть - true
//     *
//     */

//    QFile jsonFile(JSON_FILE_PATH);
//    jsonFile.open(QFile::ReadOnly);

//    //TODO: парсинг всех данных из файла

//    jsonFile.close();

//    return true;

//}

/*
QString Doctor::getProfileShortName(QString fullName)
{

}
*/
