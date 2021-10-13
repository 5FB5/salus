#include "doctor.h"

Doctor::Doctor(QString fullName, QString specialization, // for profile registration
               QString institutionName, QString institutionCode, QString institutionAddress,
               QString inn, QString licenseInfo)
{
    bFullName = fullName;
    bSpecialization = specialization;
    bInstitutionName = institutionName;
    bInstitutionCode = institutionCode;
    bInstitutionAddress = institutionAddress;
    bInn = inn;
    bLicenseInfo = licenseInfo;

    // создаём глобальный объект JSON для создания структуры файла с подкатегориями
    QJsonObject jsonGlobalObj;

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
     *  ...
     *
     * }
     *
     */

    // объект для добавления данных нового пользователя в структуру
    QJsonObject doctorProfileObj;

    doctorProfileObj.insert("specialization", specialization);
    doctorProfileObj.insert("institutionName", institutionName);
    doctorProfileObj.insert("institutionCode", institutionCode);
    doctorProfileObj.insert("institutionAddress", institutionAddress);
    doctorProfileObj.insert("inn", inn);
    doctorProfileObj.insert("licenseInfo", licenseInfo);

    jsonGlobalObj[(QString)fullName] = doctorProfileObj;

    saveProfileToJson(jsonGlobalObj);
}

void Doctor::saveProfileToJson(QJsonObject jsonObj)
{
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObj);

    QFile jsonFile(JSON_FILE_PATH);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(jsonDocument.toJson());
    jsonFile.close();
}
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
    QJsonObject currentDoctorProfile;

    jsonFile.open(QFile::ReadOnly);

}
*/

/*
QString Doctor::getDoctorShortName(QString fullName)
{

}
*/
