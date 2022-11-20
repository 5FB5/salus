#include "patientdatabase.h"


PatientDataBase::PatientDataBase(QObject *parent ): QObject(parent)
{
    getPatientsListFromJson();
}

/*!
 * \brief Добавляет нового пациента в БД
 * \param fullName ФИО
 * \param age Возраст
 * \param sex Пол
 * \param birthDate Дата рождения
 * \param address Адрес проживания
 * \param phoneNumber Номер телефона
 * \param occupation Профессия
 */
void PatientDataBase::addNewPatient(QString fullName, quint16 age, bool sex,
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

/*!
 * \brief Добавляет новую запись в амбулаторную карту пациента
 * \param birthDate Дата рождения. Используется для поиска пациента
 * \param recordDate Дата записи
 * \param anamnesis Анамнез
 * \param complaints Жалобы
 * \param diseases Перенесённые заболевания
 * \param diagnosis Текущий диагноз
 * \param treatment Наименование лечения
 */
bool PatientDataBase::addNewRecord(QString birthDate, QString recordDate, QString anamnesis, QString complaints,
                                   QString diseases, QString diagnosis, QString treatment)
{
    for (auto &p : *patientsList) {
        if (p.birthDate == birthDate) {

            if (p.cardRecords.isEmpty()) {
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
            else {
                // Проверяем список на наличие записи по указанной дате
                for (auto const &r : p.cardRecords) {
                    if (r.date == recordDate) {
                        return false;
                    }
                }

                for (auto const &r : p.cardRecords) {
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
    }
    return false;
}

/*!
 * \brief Перезагружает БД
 */
void PatientDataBase::reloadDatabase()
{
    getPatientsListFromJson();
}

/*!
 * \brief Обновляет данные БД пациентов в patients.json
 */
void PatientDataBase::updateDbToFile()
{
    QJsonDocument jsonDocument;

    QJsonArray jsonArray = jsonDocument.array();
//    QJsonArray patientProfileRecords;

    foreach (Patient p, *patientsList) {
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

    if (fInfo.exists() == true) {
       jsonFile.remove();
       jsonFile.open(QFile::WriteOnly);
       jsonFile.write(jsonDocument.toJson());
       jsonFile.close();
    }

    qDebug() << "Salus: [PatienDataBase::updateDbToFile()] - Database updated\n";
}

void PatientDataBase::updateRecord(QString birthDate, QString recordDate, QString anamnesis, QString complaints, QString diseases, QString diagnosis, QString treatment)
{
    for (auto &p : *patientsList) {
        if (p.birthDate == birthDate) {
            for (auto &r : p.cardRecords) {
                if (r.date == recordDate) {
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
    for (auto &p : *patientsList) {
        if (p.birthDate == birthDate) {
            for (int i = 0; i < p.cardRecords.size(); i++) {
                if (p.cardRecords[i].date == recordDate) {
                    p.cardRecords.removeAt(i);
                }
            }
        }
    }
}

/*!
 * \brief Удаляет пациента из БД по указанному параметру
 * \param birthDate
 * \return true, если удаление прошло успешно
 */
bool PatientDataBase::deletePatient(QString birthDate)
{
    int i = 0;
    if (patientsList->isEmpty() == false) {
        foreach(Patient patient, *patientsList) {
            if (patient.birthDate == birthDate) {
                patientsList->removeAt(i);
                return true;
            }
            else {
                i++;
            }
        }
    }
    return false;
}

/*!
 * \param birthDate
 * \return ФИО пациента по указанному параметру
 */
QString PatientDataBase::getFullName(QString birthDate)
{
    if (patientsList->isEmpty() == false) {
        foreach(Patient patient, *patientsList) {
            if (patient.birthDate == birthDate) {
                return patient.fullName;
            }
        }
    }
    return nullptr;
}

/*!
 * \param birthDate
 * \return Пол пациента по указанному параметру в соответствии с Patient::SexType
 */
bool PatientDataBase::getSex(QString birthDate)
{
    if (patientsList->isEmpty() == false) {
        foreach(Patient patient, *patientsList) {
            if (patient.birthDate == birthDate) {
                return patient.sex == Patient::SexType::MAN ? Patient::SexType::MAN : Patient::SexType::WOMAN;
            }
        }
    }
    return false;
}

/*!
 * \param birthDate
 * \return Дату рождения пациента по указанному параметру, если профиль существует
 */
QString PatientDataBase::getBirthDate(QString birthDate)
{
    if (patientsList->isEmpty() == false) {
        foreach(Patient patient, *patientsList) {
            if (patient.birthDate == birthDate) {
                return patient.birthDate;
            }
        }
    }
    return nullptr;
}

/*!
 * \param birthDate
 * \return Адрес проживания пациента по указанному параметру
 */
QString PatientDataBase::getAddress(QString birthDate)
{
    if (patientsList->isEmpty() == false) {
        foreach(Patient patient, *patientsList) {
            if (patient.birthDate == birthDate) {
                return patient.address;
            }
        }
    }
    return nullptr;
}

/*!
 * \param birthDate
 * \return Возвращает профессию пациента по указанному параметру
 */
QString PatientDataBase::getOccupation(QString birthDate)
{
    if (patientsList->isEmpty() == false) {
        foreach(Patient patient, *patientsList) {
            if (patient.birthDate == birthDate) {
                return patient.occupation;
            }
        }
    }
    return nullptr;
}

/*!
 * \param birthDate
 * \return Список записей амбулаторной карты пациента по указанному параметру
 */
QStringList PatientDataBase::getRecordsList(QString birthDate)
{
    QStringList list;

    if (patientsList->isEmpty() == false) {
        for (const auto &patient : *patientsList) {
            if (patient.birthDate == birthDate) {
                for (const auto &record : patient.cardRecords) {
                    list.append(record.date);
                }
                return list;
            }
        }
    }
    return QStringList();
}

QString PatientDataBase::getAnamnesis(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList) {
        if (p.birthDate == birthDate) {
            for (const auto &r : p.cardRecords) {
                if (r.date == recordDate) {
                    return r.anamnesis;
                }
            }
        }
    }
    return "";
}

QString PatientDataBase::getComplaints(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList) {
        if (p.birthDate == birthDate) {
            for (const auto &r : p.cardRecords) {
                if (r.date == recordDate) {
                    return r.complaints;
                }
            }
        }
    }
    return "";
}

QString PatientDataBase::getDiagnosis(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList) {
        if (p.birthDate == birthDate) {
            for (const auto &r : p.cardRecords) {
                if (r.date == recordDate) {
                    return r.currentDiagnosis;
                }
            }
        }
    }
    return "";
}

QString PatientDataBase::getDiseases(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList) {
        if (p.birthDate == birthDate) {
            for (const auto &r : p.cardRecords) {
                if (r.date == recordDate) {
                    return r.diseases;
                }
            }
        }
    }
    return "";
}

QString PatientDataBase::getTreatment(QString birthDate, QString recordDate)
{
    for (const auto &p : *patientsList) {
        if (p.birthDate == birthDate) {
            for (const auto &r : p.cardRecords) {
                if (r.date == recordDate) {
                    return r.treatment;
                }
            }
        }
    }
    return "";
}

void PatientDataBase::saveCardPdf(QString birthDate)
{
    // открыть файл
    // прочитать содержимое
    // найти метки (ФИО и т.д.)
    // подставить значения

    QString fileName;

    for (const auto &p : *patientsList)
    {
        if (p.birthDate == birthDate)
        {
            fileName = p.fullName + p.birthDate;
            fileName.remove(' ');
            fileName.replace('.', '_');
            break;
        }
    }

    QFile file("://cards_src/dentist_043_header.html");
    file.open(QIODevice::ReadOnly);

    QTextStream input(&file);
    QString html = input.readAll();

    file.close();

    QString path = QFileDialog::getSaveFileName(nullptr, "Сохранить в PDF", fileName, "PDF (*.pdf)");

    if (QFileInfo(path).suffix().isEmpty())
        path.append(".pdf");

    QPrinter printer(QPrinter::PrinterResolution);
    QTextDocument doc;

    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(path);

    doc.setHtml(html);
    doc.setPageSize(printer.pageRect().size());
    doc.print(&printer);
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

/*!
 * \param birthDate
 * \return Возраст пациента по указанному параметру
 */
quint16 PatientDataBase::getAge(QString birthDate)
{
    if (patientsList->isEmpty() == false) {
        foreach(Patient patient, *patientsList) {
            if (patient.birthDate == birthDate) {
                return patient.age;
            }
        }
    }
    return 0;
}

/*!
 * \param birthDate
 * \return Номер телефона пациента по указанному параметру
 */
QString PatientDataBase::getPhoneNumber(QString birthDate)
{
    if (patientsList->isEmpty() == false) {
        foreach(Patient patient, *patientsList) {
            if (patient.birthDate == birthDate) {
                return patient.phoneNumber;
            }
        }
    }
    return 0;
}

/*!
 * \brief Загружает список пациентов из patients.json
 */
void PatientDataBase::getPatientsListFromJson()
{
    QJsonDocument doc = loadJson();

    if (patientsList == nullptr) {
        patientsList = new QList<Patient>;
    }

    Patient currentProfile;

    QJsonArray array = doc.array();

    QJsonObject currentObj;

    if (array.isEmpty() == false) {
        if (patientsList->isEmpty() != true)
            patientsList->clear();

        foreach(const QJsonValue &v, array) {
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
}

/*!
 * \brief Сохраняет профиль пациента в patients.json по указанному параметру
 * \param patientProfile
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

/*!
 * \param birthDate
 * \return true, если профиль по указанному параметру существует
 */
bool PatientDataBase::isProfileExists(QString birthDate) {
    if (patientsList->isEmpty() == false) {
        foreach (Patient currentDoctor, *patientsList) {
            if (currentDoctor.birthDate == birthDate) {
                return true;
            }
            else {
                continue;
            }
        }
    }
    return false;
}

/*!
 * \brief Загружает содержимое файла patients.json
 * \return Содержимое файла как QJsonDocument
 */
QJsonDocument PatientDataBase::loadJson()
{
    QFileInfo fInfo(JSON_PATIENT_FILE_PATH);
    QFile f(JSON_PATIENT_FILE_PATH);

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

/*!
 * \param list
 * \return Список пациентов в формате QJsonArray по указанному параметру
 */
QJsonArray PatientDataBase::convertListToJsonArray(const QList<QString> &list)
{
    QJsonArray array;

    for (const auto &data : list) {
        array.append(data);
    }
    return array;
}

/*!
 * \param list
 * \return Список записей в формате QJsonArray по указанному параметру
 */
QJsonArray PatientDataBase::convertRecordsToJsonArray(const QList<Record_t> &records)
{
    QJsonArray array; //, arrayComplaints, arrayDiseases;

    for (const auto &data : records) {
        QJsonObject recordObject;

//        for (const auto &complaintsData : data.complaints) {
//            arrayComplaints.append(complaintsData);
//        }

//        for (const auto &diseasesData : data.diseases) {
//            arrayDiseases.append(diseasesData);
//        }

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

/*!
 * \param recordsArray
 * \return JSON массив записей в QList<Record_t> по указанному параметру
 */
QList<Record_t> PatientDataBase::convertJsonRecordsToList(const QJsonArray recordsArray)
{
//    QJsonArray jsonDiseases, jsonComplaints;
    QList<Record_t> tmpArray;
    Record_t tmpRecord;

    for (const auto &record : recordsArray) {

//        jsonDiseases = record["diseases"].toArray();
//        jsonComplaints = record["complaints"].toArray();

//        for (const auto &d : jsonDiseases) {
//            tmpRecord.diseases.append(d.toString());
//        }

//        for (const auto &c : jsonComplaints) {
//            tmpRecord.diseases.append(c.toString());
//        }

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
