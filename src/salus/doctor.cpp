#include "doctor.h"

Doctor::Doctor(QString fullName, QString specialization,
               QString institutionName, QString institutionCode, QString institutionAddress,
               QString inn, QString licenseInfo)
{
    /* Пример структуры
     *
     * {
     *
     *  "Евгений Петрович Смирнов" : {
     *      "specialization": "Наименование специализации врача",
     *      "institutionName": "Наименование учреждения",
     *      "institutionCode": "Код учреждения",
     *      "institutionAddress": "Адрес учреждения",
     *      "inn": "ИНН",
     *      "licenseInfo": "Наименование лицензии"
     *   }
     *
     * }
     *
     */

   /* if (isProfileExists(fullName) == false) {
        qDebug() << "Salus: [Doctor.h] profile '" + fullName + "' already exists\n";
        return;
    }
*/
    QJsonDocument jsonDocument = loadJson();
    QJsonArray jsonArray = jsonDocument.array();

    // создаём глобальный объект JSON для создания структуры файла с подкатегориями
    QJsonObject jsonGlobalObj;

    // объект для добавления данных нового пользователя в структуру
    QJsonObject doctorProfileObj;

    doctorProfileObj.insert("specialization", specialization);
    doctorProfileObj.insert("institutionName", institutionName);
    doctorProfileObj.insert("institutionCode", institutionCode);
    doctorProfileObj.insert("institutionAddress", institutionAddress);
    doctorProfileObj.insert("inn", inn);
    doctorProfileObj.insert("licenseInfo", licenseInfo);

    jsonGlobalObj[(QString)fullName] = doctorProfileObj;
    jsonArray.append(jsonGlobalObj);

    saveProfileToJson(jsonArray);
}

QJsonDocument Doctor::loadJson()
{
    QFileInfo fInfo(JSON_FILE_PATH);

    if (fInfo.exists()) {
        QFile f(JSON_FILE_PATH);
        f.open(QFile::ReadOnly);
        QJsonDocument jd = QJsonDocument().fromJson(f.readAll());
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

void Doctor::saveProfileToJson(QJsonArray jsonArray)
{
    QJsonDocument jsonDocument;
    jsonDocument.setArray(jsonArray);

    QFile jsonFile(JSON_FILE_PATH);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(jsonDocument.toJson());
    jsonFile.close();

    qDebug() << "Salus: [Doctor.h] saveProfileToJson() - object saved\n";
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
void Doctor::loadDataFromJson(QString doctorFullName)
{

    QFileInfo jsonFileInfo(JSON_FILE_PATH);

    if (!jsonFileInfo.exists()) {
        qDebug() << "Salus: doctors.json doesn't exists\n";
        return;
    }

    QFile jsonFile("doctors.json");

    QJsonDocument jsonDocument;

    jsonFile.open(QFile::ReadOnly);

}
*/

/*
QString Doctor::getDoctorShortName(QString fullName)
{

}
*/
