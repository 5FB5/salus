#include "patientdatabase.h"


PatientDataBase::PatientDataBase(QObject *parent ): QObject(parent)
{
    getPatientsListFromJson();
}


void PatientDataBase::addNewPatient(QString fullName, quint16 age, bool sex,
                                    QString birthDate, QString address,
                                    quint16 phoneNumber, QString occupation,
                                    QString diagnosis, QList<QString> complaints, QList<QString> diseases,
                                    QString anamnesis)
{

    // Структура профиля в patients.json. Представлен, как массив объектов со внутренними полями типа "ключ->значение"
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
    //            "diagnosis": "Острый пульпит" диагноз
    //            "complaints": [                                           // Список жалоб
    //              ]
    //            "diseases": [                                             // Список перенесенных заболеваний
    //                "Парадонтоз"
    //            ]
    //            "anamnesis": "текст"                                      // Анамнез
    //        },
    //          ... следующий профиль
    //    ]

    if (patientsList->isEmpty()){
        patientsList = new QList<Patient>;
    }
    else {
        if (isProfileExists(birthDate)) {
            qDebug() << "Salus: [PatienDataBase.h] addNewPatient() - Patient " << fullName << " already exists. Selecting this profile...\n";
        }
        return;
    }

    Patient newPatient;

    newPatient.fullName = fullName;
    newPatient.age = age;
    newPatient.sex = sex;
    newPatient.birthDate = birthDate;
    newPatient.address = address;
    newPatient.phoneNumber = phoneNumber;
    newPatient.occupation = occupation;
    newPatient.currentDiagnosis = diagnosis;
    newPatient.complaints = complaints;
    newPatient.diseases = diseases;
    newPatient.anamnesis = anamnesis;

    patientsList->append(newPatient);

    qDebug() << "Salus: [PatientDataBase.h] addNewPatient() - Saving new profile...\n";
    saveProfileToJson(newPatient);

}

// TODO: must be tested
void PatientDataBase::deletePatient(QString birthDate)
{
    if (patientsList->isEmpty() == false) {
        for(int i = 0; i < patientsList->size(); ++i) {
            foreach(Patient patient, *patientsList) {
                if (patient.birthDate == birthDate) {
                    patientsList->removeAt(i);
                }
            }
        }
    }
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
                return patient.sex;
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

QString PatientDataBase::getDiagnosis(QString birthDate)
{
    if (patientsList->isEmpty() == false) {
        foreach(Patient patient, *patientsList) {
            if (patient.birthDate == birthDate) {
                return patient.currentDiagnosis;
            }
        }
    }
    return nullptr;
}

QString PatientDataBase::getAnamnesis(QString birthDate)
{
    if (patientsList->isEmpty() == false) {
        foreach(Patient patient, *patientsList) {
            if (patient.birthDate == birthDate) {
                return patient.anamnesis;
            }
        }
    }
    return nullptr;
}

QList<QString> PatientDataBase::getDiseasesList(QString birthDate)
{
    if (patientsList->isEmpty() == false) {
        foreach(Patient patient, *patientsList) {
            if (patient.birthDate == birthDate) {
                return patient.diseases;
            }
        }
    }
}

QList<QString> PatientDataBase::getComplaintsList(QString birthDate)
{
    if (patientsList->isEmpty() == false) {
        foreach(Patient patient, *patientsList) {
            if (patient.birthDate == birthDate) {
                return patient.complaints;
            }
        }
    }
}

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

quint16 PatientDataBase::getPhoneNumber(QString birthDate)
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

    patientsList = new QList<Patient>;

    Patient currentProfile;

    QJsonArray array = doc.array(), currentObjDiseases, currentObjComplaints;
    QJsonObject currentObj;

    if (array.isEmpty() == false) {
        foreach(const QJsonValue &v, array) {

            currentObj = v.toObject();

            currentProfile.fullName = currentObj["fullname"].toString();
            currentProfile.age = currentObj["age"].toInt();
            currentProfile.sex = currentObj["sex"].toInt();
            currentProfile.birthDate = currentObj["birthdate"].toString();
            currentProfile.address = currentObj["address"].toString();
            currentProfile.birthDate = currentObj["birthDate"].toInt();
            currentProfile.phoneNumber = currentObj["phoneNumber"].toInt();
            currentProfile.occupation = currentObj["occupation"].toString();
            currentProfile.currentDiagnosis = currentObj["diagnosis"].toString();
            currentProfile.anamnesis = currentObj["anamnesis"].toString();

            currentObjDiseases = currentObj["diseases"].toArray();
            currentObjComplaints = currentObj["complaints"].toArray();

            foreach(QJsonValue v, currentObjDiseases) {
                currentProfile.diseases.append(v.toString());
            }

            foreach(QJsonValue v, currentObjComplaints) {
                currentProfile.complaints.append(v.toString());
            }

            patientsList->append(currentProfile);
        }
    }
}

void PatientDataBase::saveProfileToJson(Patient patientProfile)
{
    QJsonDocument jsonDocument = loadJson();
    QJsonArray jsonArray = jsonDocument.array(), patientProfileDiseases, patientProfileComplaints;
    QJsonObject PatientProfileObj;

    patientProfileDiseases = convertListToJsonArray(patientProfile.diseases);
    patientProfileComplaints = convertListToJsonArray(patientProfile.complaints);

    PatientProfileObj.insert("fullName", patientProfile.fullName);
    PatientProfileObj.insert("age", patientProfile.age);
    PatientProfileObj.insert("sex", patientProfile.sex);
    PatientProfileObj.insert("birthDate", patientProfile.birthDate);
    PatientProfileObj.insert("address", patientProfile.address);
    PatientProfileObj.insert("birthDate", patientProfile.birthDate);
    PatientProfileObj.insert("phoneNumber", patientProfile.phoneNumber);
    PatientProfileObj.insert("occupation", patientProfile.occupation);
    PatientProfileObj.insert("diagnosis", patientProfile.currentDiagnosis);
    PatientProfileObj.insert("anamnesis", patientProfile.anamnesis);

    PatientProfileObj.insert("diseases", patientProfileDiseases);
    PatientProfileObj.insert("complaints", patientProfileDiseases);

    jsonArray.append(PatientProfileObj);

    jsonDocument.setArray(jsonArray);

    QFile jsonFile(JSON_PATIENT_FILE_PATH);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(jsonDocument.toJson());
    jsonFile.close();

    qDebug() << "\tSalus: [PatienDataBase.h] saveProfileToJson() - Profile saved\n";
}

bool PatientDataBase::isProfileExists(QString birthDate) {
    if (patientsList->isEmpty() == false) {
        foreach (Patient currentDoctor, *patientsList) {
            if (currentDoctor.birthDate == birthDate) {
                return true;
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
