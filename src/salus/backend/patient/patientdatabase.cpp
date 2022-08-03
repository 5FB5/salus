#include "patientdatabase.h"


PatientDataBase::PatientDataBase(QObject *parent ): QObject(parent)
{
    getPatientsListFromJson();
}


void PatientDataBase::addNewPatient(QString fullName, quint16 age, bool sex,
                                    QString birthDate, QString address,
                                    QString phoneNumber, QString occupation)
{

    // Структура профиля в patients.json
    // [
    //        {
    //
    //            "fullname": "Иванов Иван Иванович",
    //            "age": ,                                                  // количество полных лет
    //            "sex": "0",                                               // (enum MAN = 0 / WOMAN = 1)
    //            "birthdate": "20.11.2000",                                // day.month.year
    //            "address": "ул. Пролетарская 25 д.222"
    //            "phoneNumber": "8 989 330 1309",
    //            "occupation": "Слесарь 4 разряда" профессия
    //
    //            "records": [
    //              {
    //                  "data": "12.12.2020                                // Дата составления записи
    //                  "diagnosis": "Острый пульпит" диагноз
    //                  "complaints": [                                           // Список жалоб
    //                  ]
    //                  "diseases": [                                             // Список перенесенных заболеваний
    //                      "Парадонтоз"
    //                  ]
    //                  "anamnesis": "текст"                                      // Анамнез
    //                  "treatment": "текст"
    //               ]
    //
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

void PatientDataBase::reloadDatabase()
{
    getPatientsListFromJson();
}

void PatientDataBase::updateDbToFile()
{
    QJsonDocument jsonDocument;

    QJsonArray jsonArray = jsonDocument.array();
    QJsonArray patientProfileRecords;

    foreach(Patient p, *patientsList) {
        QJsonObject PatientProfileObj;

        patientProfileRecords = convertRecordsToJsonArray(p.cardRecords);

        PatientProfileObj.insert("fullname", p.fullName);
        PatientProfileObj.insert("age", p.age);
        PatientProfileObj.insert("sex", p.sex);
        PatientProfileObj.insert("birthdate", p.birthDate);
        PatientProfileObj.insert("address", p.address);
        PatientProfileObj.insert("phoneNumber", p.phoneNumber);
        PatientProfileObj.insert("occupation", p.occupation);

        PatientProfileObj.insert("records", patientProfileRecords);

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

void PatientDataBase::getPatientsListFromJson()
{
    QJsonDocument doc = loadJson();

    if (patientsList == nullptr) {
        patientsList = new QList<Patient>;
    }

    Patient currentProfile;

    QJsonArray array = doc.array();
    QJsonArray currentObjDiseases, currentObjComplaints;

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

            // TODO: сконвертировать Json array в QList<Records>
//            currentProfile.cardRecords = currentObj["records"].toArray();

            patientsList->append(currentProfile);
        }
    }
}

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

QJsonArray PatientDataBase::convertListToJsonArray(const QList<QString> &list)
{
    QJsonArray array;

    for (auto &data : list) {
        array.append(data);
    }
    return array;
}

QJsonArray PatientDataBase::convertRecordsToJsonArray(const QList<Record> &records)
{
    QJsonArray array, arrayComplaints, arrayDiseases;
    QJsonObject recordObject;

    for (auto &data : records) {

        for (auto &complaintsData : data.complaints) {
            arrayComplaints.append(complaintsData);
        }


        for (auto &diseasesData : data.diseases) {
            arrayDiseases.append(diseasesData);
        }

        recordObject.insert("data", data.data);
        recordObject.insert("diagnosis", data.currentDiagnosis);
        recordObject.insert("anamnesis", data.anamnesis);
        recordObject.insert("treatment", data.treatment);

        recordObject.insert("complaints", arrayComplaints);
        recordObject.insert("diseases", arrayDiseases);

        array.append(recordObject);
    }
    return array;
}
