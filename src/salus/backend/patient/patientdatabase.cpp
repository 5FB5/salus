#include "patientdatabase.h"


PatientDataBase::PatientDataBase(QObject *parent ): QObject(parent)
{
    getPatientsListFromJson();
    webView = new QWebEngineView();
}

PatientDataBase::~PatientDataBase()
{
    delete webView;
}

/**
 * @brief  Добавляет нового пациента в БД
 * @param fullName
 * @param age
 * @param sex
 * @param birthDate
 * @param address
 * @param phoneNumber
 * @param occupation
 */
void PatientDataBase::addNewPatient(QString fullName, int age, bool sex,
                                    QString birthDate, QString address,
                                    QString phoneNumber, QString occupation)
{

    // Структура профиля в patients.json
    // [
    //        {
    //
    //            "fullname": "Иванов Иван Иванович",
    //            "age": 22,                                                // количество полных лет
    //            "sex": false,                                             // MAN = 0 / WOMAN = 1
    //            "birthdate": "20.11.2000",                                // day.month.year
    //            "address": "ул. Пролетарская 25 д.222"
    //            "phoneNumber": "8 989 330 1309",
    //            "occupation": "Слесарь 4 разряда" профессия
    //
    //            "records":
    //              [
    //                  {
    //                      "data": "12.12.2020                             // Дата составления записи
    //                      "diagnosis": "Острый пульпит" диагноз
    //                      "complaints": [                                 // Список жалоб
    //                      ]
    //                      "diseases": [                                   // Список перенесенных заболеваний
    //                        "Парадонтоз"
    //                      ]
    //                      "anamnesis": "текст"                            // Анамнез
    //                      "treatment": "текст"
    //
    //                  },
    //                  ... следующая запись
    //              ]
    //        },
    //          ... следующий профиль
    //    ]

    if (patientsList == nullptr){
        patientsList = new QList<Patient>;
    }
    else {
        if (isProfileExists(birthDate) == true) {
            qDebug() << "Salus: [PatienDataBase::addNewPatient()] - Patient " << fullName << " already exists. Selecting this profile...\n";
            return;
        }
    }

    Patient newPatient;

    newPatient.fullName = fullName;
    newPatient.age = age;
    newPatient.sex = sex;
    newPatient.birthDate = birthDate;
    newPatient.address = address;
    newPatient.phoneNumber = phoneNumber;
    newPatient.occupation = occupation;

    patientsList->append(newPatient);

    qDebug() << "Salus: [PatientDataBase::addNewPatient()] - Saving new profile...\n";
    saveProfileToJson(newPatient);
}

/**
 * @brief Добавляет новую запись в амбулаторную карту пациента
 * @param birthDate
 * @param recordDate
 * @param anamnesis
 * @param complaints
 * @param diseases
 * @param diagnosis
 * @param treatment
 * @return
 */
bool PatientDataBase::addNewRecord(QString birthDate, QString recordDate, QString anamnesis, QString complaints,
                                   QString diseases, QString diagnosis, QString treatment)
{
    for (auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            if (p.cardRecords.isEmpty())
            {
                Record_t newRecord;

                newRecord.date = recordDate;
                newRecord.currentDiagnosis = diagnosis;
                newRecord.anamnesis = anamnesis;
                newRecord.complaints = complaints;
                newRecord.diseases = diseases;
                newRecord.treatment = treatment;

                p.cardRecords.append(newRecord);

                return true;
            }
            else
            {
                // Проверяем список на наличие записи по указанной дате
                for (const auto &r : p.cardRecords)
                {
                    if (r.date == recordDate)
                        return false;
                }

                Record_t newRecord;

                newRecord.date = recordDate;
                newRecord.currentDiagnosis = diagnosis;
                newRecord.anamnesis = anamnesis;
                newRecord.complaints = complaints;
                newRecord.diseases = diseases;
                newRecord.treatment = treatment;

                p.cardRecords.append(newRecord);

                return true;
            }
        }
    }
    return false;
}

void PatientDataBase::reloadDatabase()
{
    getPatientsListFromJson();
}

/**
 * @brief Обновляет данные БД пациентов в patients.json
 */
void PatientDataBase::updateDbToFile()
{
    QJsonDocument jsonDocument;

    QJsonArray jsonArray = jsonDocument.array();

    foreach (Patient p, *patientsList)
    {
        QJsonObject PatientProfileObj;

        PatientProfileObj.insert("fullname", p.fullName);
        PatientProfileObj.insert("age", p.age);
        PatientProfileObj.insert("sex", p.sex);
        PatientProfileObj.insert("birthdate", p.birthDate);
        PatientProfileObj.insert("address", p.address);
        PatientProfileObj.insert("phoneNumber", p.phoneNumber);
        PatientProfileObj.insert("occupation", p.occupation);

        PatientProfileObj.insert("records", convertRecordsToJsonArray(p.cardRecords));

        jsonArray.append(PatientProfileObj);
    }

    jsonDocument.setArray(jsonArray);

    QFileInfo fInfo(JSON_PATIENT_FILE_PATH);
    QFile jsonFile(JSON_PATIENT_FILE_PATH);

    if (fInfo.exists() == true)
    {
       jsonFile.remove();
       jsonFile.open(QFile::WriteOnly);
       jsonFile.write(jsonDocument.toJson());
       jsonFile.close();
    }

    qDebug() << "Salus: [PatienDataBase::updateDbToFile()] - Database updated\n";
}

/**
 * @brief Обновляет запись пациента
 * @param birthDate
 * @param recordDate
 * @param anamnesis
 * @param complaints
 * @param diseases
 * @param diagnosis
 * @param treatment
 */
void PatientDataBase::updateRecord(QString birthDate, QString recordDate, QString anamnesis, QString complaints, QString diseases, QString diagnosis, QString treatment)
{
    for (auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (auto &r : p.cardRecords)
            {
                if (r.date == recordDate)
                {
                    r.anamnesis = anamnesis;
                    r.complaints = complaints;
                    r.currentDiagnosis = diagnosis;
                    r.diseases = diseases;
                    r.treatment = treatment;
                    break;
                }
            }
        }
    }
}

void PatientDataBase::deleteRecord(QString birthDate, QString recordDate)
{
    for (auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (int i = 0; i < p.cardRecords.size(); i++)
            {
                if (p.cardRecords[i].date == recordDate)
                    p.cardRecords.removeAt(i);
            }
        }
    }
}

/**
 * @brief Удаляет пациента из БД по указанному параметру
 * @param birthDate
 * @return true, если удаление прошло успешно
 */
bool PatientDataBase::deletePatient(QString birthDate)
{
    int i = 0;

    if (patientsList->isEmpty() == true)
        return false;

    foreach(Patient patient, *patientsList)
    {
        if (patient.birthDate == birthDate)
        {
            patientsList->removeAt(i);
            return true;
        }
        else
            i++;

    }
    return false;
}

QString PatientDataBase::getFullName(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return "";

    foreach(Patient patient, *patientsList)
    {
        if (patient.birthDate == birthDate)
            return patient.fullName;
    }
    return "";
}

bool PatientDataBase::getSex(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return false;

    foreach(Patient patient, *patientsList)
    {
        if (patient.birthDate == birthDate)
            return patient.sex == Patient::SexType::MAN ? Patient::SexType::MAN : Patient::SexType::WOMAN;
    }
    return false;
}

QString PatientDataBase::getBirthDate(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return "";

        foreach(Patient patient, *patientsList)
        {
            if (patient.birthDate == birthDate)
                return patient.birthDate;
        }
    return "";
}

QString PatientDataBase::getAddress(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return "";

    foreach(Patient patient, *patientsList)
    {
        if (patient.birthDate == birthDate)
            return patient.address;
    }
    return "";
}

QString PatientDataBase::getOccupation(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return "";

    foreach(Patient patient, *patientsList)
    {
        if (patient.birthDate == birthDate)
            return patient.occupation;
    }
    return "";
}

QStringList PatientDataBase::getRecordsList(QString birthDate)
{
    QStringList list;

    if (patientsList->isEmpty() == true)
        return QStringList();

    for (const auto &patient : *patientsList)
    {
        if (patient.birthDate == birthDate)
        {
            for (const auto &record : patient.cardRecords)
                list.append(record.date);
            return list;
        }
    }
    return QStringList();
}

QString PatientDataBase::getAnamnesis(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (const auto &r : p.cardRecords)
            {
                if (r.date == recordDate)
                    return r.anamnesis;
            }
        }
    }
    return "";
}

QString PatientDataBase::getComplaints(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (const auto &r : p.cardRecords)
            {
                if (r.date == recordDate)
                    return r.complaints;
            }
        }
    }
    return "";
}

QString PatientDataBase::getDiagnosis(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (const auto &r : p.cardRecords)
            {
                if (r.date == recordDate)
                    return r.currentDiagnosis;
                }
            }
        }
    return "";
}

QString PatientDataBase::getDiseases(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (const auto &r : p.cardRecords)
            {
                if (r.date == recordDate)
                    return r.diseases;
            }
        }
    }
    return "";
}

QString PatientDataBase::getTreatment(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            for (const auto &r : p.cardRecords)
            {
                if (r.date == recordDate)
                    return r.treatment;
            }
        }
    }
    return "";
}

void PatientDataBase::saveCardPdf(QString birthDate)
{
    QString fileName;

    QString patientName;
    QString sex;
    QString age;
    QString address;
    QString occupation;

    QFile file("://cards_src/dentist_043_header.html");
    file.open(QIODevice::ReadOnly);

    QTextStream input(&file);
    QString html = input.readAll();

    file.close();

    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            // Для подстановки ФИО в карту
            patientName = p.fullName;
            sex = p.sex == false ? "М" : "Ж";
            age = QString::number(p.age);
            address = p.address;
            occupation = p.occupation;

            fileName = p.fullName + p.birthDate;
            fileName.remove(' ');
            fileName.replace('.', '_');
            break;
        }
    }

    html.replace("МЕТКА_ФИО", patientName);
    html.replace("МЕТКА_ПОЛ", sex);
    html.replace("МЕТКА_ВОЗРАСТ", age);
    html.replace("МЕТКА_АДРЕС", address);
    html.replace("МЕТКА_ПРОФЕССИЯ", occupation);

    webView->setHtml(html);

    QString path = QFileDialog::getSaveFileName(nullptr, "Сохранить в PDF", fileName, "PDF (*.pdf)");

    if (QFileInfo(path).suffix().isEmpty())
        path.append(".pdf");

    QPrinter printer(QPrinter::PrinterResolution);

    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOrientation(QPrinter::Landscape);
    printer.setPaperSize(QPrinter::A5);
    printer.setOutputFileName(path);

    webView->page()->printToPdf(path);
}

//QString PatientDataBase::getDiagnosis(QString birthDate)
//{
//    if (patientsList->isEmpty() == false) {
//        foreach(Patient patient, *patientsList) {
//            if (patient.birthDate == birthDate) {
//                return patient.currentDiagnosis;
//            }
//        }
//    }
//    return nullptr;
//}

//QString PatientDataBase::getAnamnesis(QString birthDate)
//{
//    if (patientsList->isEmpty() == false) {
//        foreach(Patient patient, *patientsList) {
//            if (patient.birthDate == birthDate) {
//                return patient.anamnesis;
//            }
//        }
//    }
//    return nullptr;
//}

//QList<QString> PatientDataBase::getDiseasesList(QString birthDate)
//{
//    if (patientsList->isEmpty() == false) {
//        foreach(Patient patient, *patientsList) {
//            if (patient.birthDate == birthDate) {
//                return patient.diseases;
//            }
//        }
//    }
//}

//QList<QString> PatientDataBase::getComplaintsList(QString birthDate)
//{
//    if (patientsList->isEmpty() == false) {
//        foreach(Patient patient, *patientsList) {
//            if (patient.birthDate == birthDate) {
//                return patient.complaints;
//            }
//        }
//    }
//}

int PatientDataBase::getAge(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return 0;

        foreach(Patient patient, *patientsList)
        {
            if (patient.birthDate == birthDate)
                return patient.age;
        }
    return 0;
}

QString PatientDataBase::getPhoneNumber(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return "";

    foreach(Patient patient, *patientsList)
    {
        if (patient.birthDate == birthDate)
            return patient.phoneNumber;
    }
    return "";
}

/**
 * @brief Получает спислк пациентов из JSON файла
 */
void PatientDataBase::getPatientsListFromJson()
{
    QJsonDocument doc = loadJson();

    if (patientsList == nullptr)
        patientsList = new QList<Patient>;

    Patient currentProfile;

    QJsonArray array = doc.array();

    QJsonObject currentObj;

    if (array.isEmpty() == true)
        return;

    if (patientsList->isEmpty() == false)
        patientsList->clear();

    foreach(const QJsonValue &v, array)
    {
        currentObj = v.toObject();

        currentProfile.fullName = currentObj["fullname"].toString();
        currentProfile.age = currentObj["age"].toInt();
        currentProfile.sex = currentObj["sex"].toBool();
        currentProfile.birthDate = currentObj["birthdate"].toString();
        currentProfile.address = currentObj["address"].toString();
        currentProfile.birthDate = currentObj["birthdate"].toString();
        currentProfile.phoneNumber = currentObj["phoneNumber"].toString();
        currentProfile.occupation = currentObj["occupation"].toString();

        currentProfile.cardRecords = convertJsonRecordsToList(currentObj["records"].toArray());

        patientsList->append(currentProfile);
    }
}

/**
 * @brief Сохраняет профиль пациента в patients.json по указанному параметру
 * @param patientProfile
 */
void PatientDataBase::saveProfileToJson(Patient patientProfile)
{
    QJsonDocument jsonDocument = loadJson();

    QJsonArray jsonArray = jsonDocument.array();
    QJsonArray patientProfileRecords;

    QJsonObject PatientProfileObj;

    patientProfileRecords = convertRecordsToJsonArray(patientProfile.cardRecords);

    PatientProfileObj.insert("fullname", patientProfile.fullName);
    PatientProfileObj.insert("age", patientProfile.age);
    PatientProfileObj.insert("sex", patientProfile.sex);
    PatientProfileObj.insert("birthdate", patientProfile.birthDate);
    PatientProfileObj.insert("address", patientProfile.address);
    PatientProfileObj.insert("phoneNumber", patientProfile.phoneNumber);
    PatientProfileObj.insert("occupation", patientProfile.occupation);

    PatientProfileObj.insert("records", patientProfileRecords);

    jsonArray.append(PatientProfileObj);

    jsonDocument.setArray(jsonArray);

    QFile jsonFile(JSON_PATIENT_FILE_PATH);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(jsonDocument.toJson());
    jsonFile.close();

    qDebug() << "\tSalus: [PatienDataBase::saveProfileToJson()] - Profile saved\n";
}

bool PatientDataBase::isProfileExists(QString birthDate)
{
    if (patientsList->isEmpty() == true)
        return false;

    foreach (Patient currentDoctor, *patientsList)
    {
        if (currentDoctor.birthDate == birthDate)
            return true;
        else
            continue;
    }
    return false;
}

/**
 * @brief Загружает содержимое файла patients.json
 * @return
 */
QJsonDocument PatientDataBase::loadJson()
{
    QFileInfo fInfo(JSON_PATIENT_FILE_PATH);
    QFile f(JSON_PATIENT_FILE_PATH);

    if (fInfo.exists() == false)
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

/**
 * @brief Конвертирует QList в массив формата JSON
 * @param list
 * @return
 */
QJsonArray PatientDataBase::convertListToJsonArray(const QList<QString> &list)
{
    QJsonArray array;

    if (list.isEmpty() == true)
        return array;

    for (const auto &data : list)
        array.append(data);

    return array;
}

/**
 * @brief Конвертирует лист записей в массив формата JSON
 * @param records
 * @return
 */
QJsonArray PatientDataBase::convertRecordsToJsonArray(const QList<Record_t> &records)
{
    QJsonArray array;

    if (records.isEmpty() == true)
        return array;

    for (const auto &data : records)
    {
        QJsonObject recordObject;

        recordObject.insert("data", data.date);
        recordObject.insert("diagnosis", data.currentDiagnosis);

        recordObject.insert("anamnesis", data.anamnesis);
        recordObject.insert("treatment", data.treatment);
        recordObject.insert("complaints", data.complaints);
        recordObject.insert("diseases", data.diseases);

        array.append(recordObject);
    }
    return array;
}

/**
 * @brief Конвертирует записи формата JSON в QList
 * @param recordsArray
 * @return
 */
QList<Record_t> PatientDataBase::convertJsonRecordsToList(const QJsonArray recordsArray)
{
    QList<Record_t> tmpArray;
    Record_t tmpRecord;

    for (const auto &record : recordsArray)
    {
        tmpRecord.date = record["data"].toString();
        tmpRecord.anamnesis = record["anamnesis"].toString();
        tmpRecord.diseases = record["diseases"].toString();
        tmpRecord.complaints = record["complaints"].toString();
        tmpRecord.currentDiagnosis = record["diagnosis"].toString();
        tmpRecord.treatment = record["treatment"].toString();

        tmpArray.append(tmpRecord);
    }
    return tmpArray;
}
