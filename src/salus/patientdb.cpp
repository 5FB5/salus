#include "patientdb.h"


patientDB::patientDB(QObject *parent ): QObject(parent)
{
    getPatientListFromJson();
}


void patientDB::addNewPatient(  QString fullName, uint8_t age,
                     bool sex,
                     QDate birthDate,
                     QString adress,
                     QString insuranceCompany,
                     QString insuranceNumber,
                     QString phoneNumber,
                     QString occupation,
                     QString diagnosis,
                     QList<QString> diseases,
                     QString diseaseDescription){

    // Patient Json stracture    //    [
    //        {
    //
    //            "fullname": "Иванов Иван Иванович",
    //            "age": ,      // количество полных лет
    //            "sex": "man/woman",
    //            "birthdate": "2000.11.20", year.month.day
    //            "adress": "ул. Пролетарская 25 д.222"
    //            "insuranceCompany": "ООО Альфа-страховние",
    //            "insuranceNumber": "1029384756102938", 16 значный индивидуальный номер страховки
    //            "phoneNumber": "8 989 330 1309",
    //            "occupation": "Слесарь 4 разряда" профессия
    //            "diagnosis": "Острый пульпит" диагноз
    //            "diseases": [       // Список перенесенных заблеваний
    //                "Парадонтоз"
    //            ]
    //            "diseaseDescription": "текст" описание настоящей болезни
    //        }
    //    ]

    if (patientList->isEmpty()){
        patientList = new QList<Patient>;
    }else{

        if (isProfileExists(insuranceNumber))
            qDebug() << "Salus: [patient.h] addNewPatient() - Patient " << fullName << " already exists. Selecting this profile...\n";
            return;
    };

    Patient newPatient;

    newPatient.fullName = fullName;
    newPatient.age = age;
    newPatient.sex = sex;
    newPatient.birthDate = birthDate;
    newPatient.adress = adress;
    newPatient.insuranceCompany = insuranceCompany;
    newPatient.insuranceNumber = insuranceNumber;
    newPatient.phoneNumber = phoneNumber;
    newPatient.occupation = occupation;
    newPatient.diagnosis = diagnosis;
    newPatient.diseases = diseases;
    newPatient.diseaseDescription = diseaseDescription;

    patientList->append(newPatient);
     qDebug() << "Salus: [patinetDB.h] addNewPaitent() - Saving new profile...\n";
    saveProfileToJson(newPatient);

}
bool patientDB::saveProfileToJson(Patient patientProfile){
    QJsonDocument jsonDocument = loadJson();
        QJsonArray jsonArray = jsonDocument.array(), patientProfileDiseases;
        QJsonObject PatientProfileObj;

        patientProfileDiseases = convertListToJsonArray(patientProfile.diseases);


        PatientProfileObj.insert("fullName", patientProfile.fullName);
        PatientProfileObj.insert("age", patientProfile.age);
        PatientProfileObj.insert("sex", patientProfile.sex);
        PatientProfileObj.insert("birthDate", patientProfile.birthDate.toString());
        PatientProfileObj.insert("adress", patientProfile.adress);
        PatientProfileObj.insert("insuranceCompany", patientProfile.insuranceCompany);
        PatientProfileObj.insert("insuranceNumber", patientProfile.insuranceNumber);
        PatientProfileObj.insert("phoneNumber", patientProfile.phoneNumber);
        PatientProfileObj.insert("occupation", patientProfile.occupation);
        PatientProfileObj.insert("diagnosis", patientProfile.diagnosis);
        PatientProfileObj.insert("diseaseDescription", patientProfile.diseaseDescription);

        PatientProfileObj.insert("diseases", patientProfileDiseases);


        jsonArray.append(PatientProfileObj);

        jsonDocument.setArray(jsonArray);

        QFile jsonFile(JSON_PATIENT_FILE_PATH);
        jsonFile.open(QFile::WriteOnly);
        jsonFile.write(jsonDocument.toJson());
        jsonFile.close();

        qDebug() << "\tSalus: [DoctorDataBase.h] saveProfileToJson() - Profile saved\n";
};

bool patientDB::isProfileExists(QString insuranceNumber){

    for (Patient currentPatient : *patientList){
      if(currentPatient.insuranceNumber == insuranceNumber)
        return  true;
    }
    return false;
};

QJsonArray patientDB::convertListToJsonArray(const QList<QString> &list){
    QJsonArray array;

    for (auto &data : list) {
        array.append(data);
    }

    return array;
};


QJsonDocument patientDB::loadJson(){
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

void patientDB::getPatientListFromJson(){
    QJsonDocument doc = loadJson();

    if (doc.isEmpty() == true) {
        return;
    }

    patientList = new QList<Patient>;

    Patient currentProfile;

    QJsonArray array = doc.array(), currentObjDiseases;
    QJsonObject currentObj;

    foreach(const QJsonValue &v, array) {

        currentObj = v.toObject();

        currentProfile.fullName = currentObj["fullname"].toString();
        currentProfile.age = currentObj["specialization"].toInt();
        currentProfile.sex = currentObj["institutionName"].toBool();
        currentProfile.birthDate.toString() = currentObj["institutionCode"].toString();
        currentProfile.adress = currentObj["institutionAddress"].toString();
        currentProfile.insuranceCompany = currentObj["licenseInfo"].toString();
        currentProfile.insuranceNumber = currentObj["inn"].toString();
        currentProfile.phoneNumber = currentObj["inn"].toString();
        currentProfile.occupation = currentObj["inn"].toString();
        currentProfile.diagnosis = currentObj["inn"].toString();
        currentProfile.diseaseDescription = currentObj["inn"].toString();


        currentObjDiseases = currentObj["diseases"].toArray();


        foreach(QJsonValue v, currentObjDiseases) {
            currentProfile.diseases.append(v.toString());
        }



        patientList->append(currentProfile);
    }
}
