#include "doctordatabase.h"

DoctorDataBase::DoctorDataBase(QObject *parent) : QObject(parent)
{
    getDoctorsListFromJson();
}

DoctorDataBase::~DoctorDataBase()
{
    updateDbToFile();
}

/**
 * @brief Обновляет данные БД врачей в doctors.json
 */
void DoctorDataBase::updateDbToFile()
{
    QJsonDocument jsonDocument;
    QJsonArray jsonArray = jsonDocument.array();

    foreach (Doctor doctorProfile, *doctorsList)
    {
        QJsonObject DoctorProfileObj;

        DoctorProfileObj.insert("fullname", doctorProfile.fullName);
        DoctorProfileObj.insert("specialization", doctorProfile.specialization);
        DoctorProfileObj.insert("institutionName", doctorProfile.institutionName);
        DoctorProfileObj.insert("institutionCode", doctorProfile.institutionCode);
        DoctorProfileObj.insert("institutionAddress", doctorProfile.institutionAddress);
        DoctorProfileObj.insert("inn", doctorProfile.inn);
        DoctorProfileObj.insert("licenseInfo", doctorProfile.licenseInfo);
        DoctorProfileObj.insert("initials", doctorProfile.initials);

        jsonArray.append(DoctorProfileObj);

        jsonDocument.setArray(jsonArray);

        QFile jsonFile(JSON_DOCTOR_FILE_PATH);
        jsonFile.open(QFile::WriteOnly);
        jsonFile.write(jsonDocument.toJson());
        jsonFile.close();
    }

    jsonDocument.setArray(jsonArray);

    QFileInfo fInfo(JSON_DOCTOR_FILE_PATH);
    QFile jsonFile(JSON_DOCTOR_FILE_PATH);

    if (fInfo.exists() == true)
    {
        jsonFile.remove();
        jsonFile.open(QFile::WriteOnly);
        jsonFile.write(jsonDocument.toJson());
        jsonFile.close();
    }

    qDebug() << "[DoctorDataBase::updateDbToFile()] - Database updated\n";

}

/**
 * @brief Создаёт новый профиль врача
 * @param fullName
 * @param specialization
 * @param institutionName
 * @param institutionCode
 * @param institutionAddress
 * @param inn
 * @param licenseInfo
 */
void DoctorDataBase::createNewProfile(QString fullName, QString specialization,
                                      QString institutionName, quint16 institutionCode, QString institutionAddress,
                                      quint16 inn, QString licenseInfo)
{

    // Структура профиля в doctors.json. Представлен, как массив объектов со внутренними полями типа "ключ->значение"
    //    [
    //            "fullname": "Иванов Иван Иванович",
    //            "inn": "0000000",
    //            "institutionAddress": "ул. Строителей, д 25, кв. 12",     // Адрес организации
    //            "institutionCode": "11111111",                            // Код организации
    //            "institutionName": "ИП Иванов И.И.",                      // Наименование организации
    //            "licenseInfo": "Лицензия №256",                           // Наименование лицензии
    //            "specialization": "Стоматолог"                            // Наименование специализации врача
    //            "initials": "Иванов И.И."                                 // Инициалы врача
    //        },
    //          ... следующий профиль
    //    ]

    if (doctorsList == nullptr)
        doctorsList = new QList<Doctor>;
    else
    {
        if (isProfileExists(inn) == true)
        {
            qDebug() << "[DoctorDataBase.h] createNewProfile() - Profile " << fullName << " already exists. Selecting this profile...\n";
            return;
        }
    }

    Doctor newDoctor;

    // Заполняем данными из введённых полей
    newDoctor.fullName = fullName;
    newDoctor.initials = generateInitials(newDoctor.fullName);
    newDoctor.specialization = specialization;
    newDoctor.institutionName = institutionName;
    newDoctor.institutionCode = institutionCode;
    newDoctor.institutionAddress = institutionAddress;
    newDoctor.inn = inn;
    newDoctor.licenseInfo = licenseInfo;

    doctorsList->append(newDoctor);

    qDebug() << "[DoctorDataBase.h] createNewProfile() - Saving new profile " << fullName << " ...\n";
    saveProfileToJson(newDoctor);
}

/**
 * @brief Генерирует инициалы из ФИО в форме "Иванов И.И."
 * @param fullName
 * @return
 */
QString DoctorDataBase::generateInitials(QString fullName)
{
    QStringList subStrings = fullName.split(" ");
    return subStrings[0] + " " + subStrings[1].at(0) + ". " + subStrings[2].at(0) + ".";
}

QString DoctorDataBase::getFullName(quint16 inn)
{
    if (doctorsList->isEmpty() == false) {
        foreach(Doctor doctor, *doctorsList) {
            if (doctor.inn == inn) {
                return doctor.fullName;
            }
        }
    }
    return nullptr;
}

QString DoctorDataBase::getSpecialization(quint16 inn)
{
    if (doctorsList->isEmpty() == true)
        return "";

    foreach(Doctor doctor, *doctorsList)
    {
        if (doctor.inn == inn)
            return doctor.specialization;
    }
    return "";
}

QString DoctorDataBase::getInstitutionName(quint16 inn)
{
    if (doctorsList->isEmpty() == true)
        return "";

    foreach(Doctor doctor, *doctorsList)
    {
        if (doctor.inn == inn)
            return doctor.institutionName;
    }
    return "";
}

quint16 DoctorDataBase::getInstitutionCode(quint16 inn)
{
    if (doctorsList->isEmpty() == true)
        return 0;

    foreach(Doctor doctor, *doctorsList)
    {
        if (doctor.inn == inn)
            return doctor.institutionCode;
    }
    return 0;
}

QString DoctorDataBase::getInstitutionAddress(quint16 inn)
{
    if (doctorsList->isEmpty() == true)
        return 0;

    foreach(Doctor doctor, *doctorsList)
    {
        if (doctor.inn == inn)
            return doctor.institutionAddress;
    }
    return 0;
}

quint16 DoctorDataBase::getInn()
{
    if (doctorsList->isEmpty() == true)
        return 0;

    foreach(Doctor doctor, *doctorsList)
    {
        return doctor.inn;
    }
    return 0;
}

QString DoctorDataBase::getLicenseInfo(quint16 inn)
{
    if (doctorsList->isEmpty() == true)
        return "";

    foreach(Doctor doctor, *doctorsList)
    {
        if (doctor.inn == inn)
            return doctor.licenseInfo;
    }
    return "";
}

QString DoctorDataBase::getProfileInitials(quint16 inn)
{
    for (const auto &it : *doctorsList)
    {
        if (it.inn == inn && it.initials != "")
            return it.initials;
    }

    return "";
}

/**
 * @brief Загружает сождержимое файла doctors.json
 * @return
 */
QJsonDocument DoctorDataBase::loadJson()
{
    QFileInfo fInfo(JSON_DOCTOR_FILE_PATH);
    QFile f(JSON_DOCTOR_FILE_PATH);

    if (!fInfo.exists())
    {
        f.open(QFile::WriteOnly);
        QJsonDocument jd;
        f.write(jd.toJson());
        f.close();
        return jd;
    }

    f.open(QFile::ReadOnly);
    QJsonDocument jd = QJsonDocument::fromJson(f.readAll());
    f.close();
    return jd;
}

/*!
 * @brief Преобразует QList<QString> в формат JSON массива
 * @param list
 * @return Массив в формате QJsonArray
 */
QJsonArray DoctorDataBase::convertListToJsonArray(const QList<QString> &list)
{
    QJsonArray array;

    if (list.isEmpty() == true)
        return array;

    for (auto &data : list)
    {
        array.append(data);
    }
    return array;
}

/*!
 * @brief Загружает профили врачей
 */
void DoctorDataBase::getDoctorsListFromJson()
{
    QJsonDocument doc = loadJson();

    doctorsList = new QList<Doctor>;

    Doctor currentProfile;

    QJsonArray array = doc.array(), currentObjDiagnoses, currentObjTreatments;
    QJsonObject currentObj;

    if (array.isEmpty() == true)
        return;

    foreach(const QJsonValue &v, array)
    {
        currentObj = v.toObject();

        currentProfile.fullName = currentObj["fullname"].toString();
        currentProfile.specialization = currentObj["specialization"].toString();
        currentProfile.institutionName = currentObj["institutionName"].toString();
        currentProfile.institutionCode = currentObj["institutionCode"].toInt();
        currentProfile.institutionAddress = currentObj["institutionAddress"].toString();
        currentProfile.licenseInfo = currentObj["licenseInfo"].toString();
        currentProfile.inn = currentObj["inn"].toInt();
        currentProfile.initials = currentObj["initials"].toString();

        if (currentProfile.initials == "")
        {
            QString initials = generateInitials(currentProfile.fullName);
            currentProfile.initials = initials;
        }

        doctorsList->append(currentProfile);
    }
}

/*!
 * @brief Сохраняет профиль врача в doctors.json
 * @param doctorProfile Профиль врача
 */
void DoctorDataBase::saveProfileToJson(Doctor doctorProfile)
{
    QJsonDocument jsonDocument = loadJson();
    QJsonArray jsonArray = jsonDocument.array();
    QJsonObject DoctorProfileObj;

    DoctorProfileObj.insert("fullname", doctorProfile.fullName);
    DoctorProfileObj.insert("specialization", doctorProfile.specialization);
    DoctorProfileObj.insert("institutionName", doctorProfile.institutionName);
    DoctorProfileObj.insert("institutionCode", doctorProfile.institutionCode);
    DoctorProfileObj.insert("institutionAddress", doctorProfile.institutionAddress);
    DoctorProfileObj.insert("inn", doctorProfile.inn);
    DoctorProfileObj.insert("licenseInfo", doctorProfile.licenseInfo);
    DoctorProfileObj.insert("initials", doctorProfile.initials);

    jsonArray.append(DoctorProfileObj);

    jsonDocument.setArray(jsonArray);

    QFile jsonFile(JSON_DOCTOR_FILE_PATH);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(jsonDocument.toJson());
    jsonFile.close();

    qDebug() << "\t[DoctorDataBase.h] saveProfileToJson() - Profile saved\n";
}

bool DoctorDataBase::isProfileExists(quint16 inn)
{
    if (doctorsList->isEmpty() == true)
        return false;

        foreach (Doctor currentDoctor, *doctorsList)
        {
            if (currentDoctor.inn == inn)
                return true;
        }
    return false;
}
