#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    // Проверка профиля на запуске
    if (doctorDb.doctorsList->size() > 0)
    {
        if (doctorDb.doctorsList->size() == 1)
            currentDoctorInn = doctorDb.getInn();
    }

    patientsDb = new PatientDataBase;
    patientListModel = new PatientListModel;
    patientRecordsListModel = new QStringListModel();

    patientListModel->patientDb.patientsList = patientsDb->patientsList;
    patientRecordsListModel->setStringList(getCurrentPatientRecords());
}

Backend::~Backend()
{
    qDebug() << "Salus: [Backend::~Backend] - updateDbToFile()\n";
    patientsDb->updateDbToFile();

    delete patientListModel;
    delete patientRecordsListModel;
    delete patientsDb;
}

/**
 * @brief Добавление свойств и типов данных в контекст QML.
 * @warning Вызов должен происходить до загрузки движком URL
 * @param context
 */
void Backend::addPropertiesToContext(QQmlContext *context)
{
    qmlRegisterType<Backend>("salus", 1, 0, "Backend");
    context->setContextProperty("backend", this);

    qmlRegisterType<PatientListModel>("salus", 1, 0, "PatientListModel");
    context->setContextProperty("patientListModel", patientListModel);

    qmlRegisterType<QStringListModel>("salus", 1, 0, "QStringListModel");
    context->setContextProperty("patientRecordsListModel", patientRecordsListModel);
}

void Backend::setPatient(QString fullName)
{
        if (!patientsDb->patientsList->isEmpty() == true)
            return;

        qDebug() << "Salus: [Backend::setPatient()] - Set patient " << fullName << "... \n";

        foreach(Patient p, *patientsDb->patientsList)
        {
            if (p.fullName == fullName)
            {
                if (p.birthDate == currentPatientBirthDate)
                {
                    qDebug() << "Salus: [Backend::setPatient()] - Patient birth date is the same with current! Return...\n";
                    return;
                }
                else
                {
                    qDebug() << "Salus: [Backend::setPatient()] - Select birth date " << p.birthDate << " of " << fullName << "...\n";
                    currentPatientBirthDate = p.birthDate;
                    patientRecordsListModel->setStringList(getCurrentPatientRecords());
                    qDebug() << "Salus: [Backend::setPatient()] - Birth date selected!\n";
                    return;
                }
            }
        }
        qDebug() << "Salus: [Backend::setPatient()] - Current patient's birth date " << fullName << " is " << currentPatientBirthDate << "\n";
}

/**
 * @brief Добавляет новый профиль врача в БД.
 * @param doctorFullName
 * @param doctorSpecialization
 * @param doctorInstitutionName
 * @param doctorInstitutionCode
 * @param doctorInstitutionAddress
 * @param doctorInn
 * @param doctorLicenseInfo
 */
void Backend::addNewDoctorProfile(QString doctorFullName, QString doctorSpecialization,
                                  QString doctorInstitutionName, quint16 doctorInstitutionCode, QString doctorInstitutionAddress,
                                  quint16 doctorInn, QString doctorLicenseInfo)
{
    doctorDb.createNewProfile(doctorFullName, doctorSpecialization,
                              doctorInstitutionName,  doctorInstitutionCode,  doctorInstitutionAddress,
                              doctorInn,  doctorLicenseInfo);

    currentDoctorInn = doctorInn;

    emit profileAdded();
}

/**
 * @brief Обновляет запись текущего пациента
 * @param recordDate
 * @param anamnesis
 * @param complaints
 * @param diseases
 * @param diagnosis
 * @param treatment
 */
void Backend::updateRecord(QString recordDate, QString anamnesis, QString complaints, QString diseases, QString diagnosis, QString treatment)
{
    patientsDb->updateRecord(currentPatientBirthDate, recordDate, anamnesis, complaints,
                             diseases, diagnosis, treatment);
    emit recordUpdated();
}

/**
 * @brief Удаляет запись текущего пациента
 * @param recordDate
 */
void Backend::deleteRecord(QString recordDate)
{
    patientsDb->deleteRecord(currentPatientBirthDate, recordDate);
    patientsDb->updateDbToFile();
    patientRecordsListModel->setStringList(getCurrentPatientRecords());
    emit recordDeleted();
}

/**
 * @brief Добавляет новый профиль пациента в БД
 * @param fullName
 * @param age
 * @param sex
 * @param birthDate
 * @param address
 * @param phoneNumber
 * @param occupation
 */
void Backend::addNewPatient(QString fullName, quint16 age, bool sex,
                            QString birthDate, QString address,
                            QString phoneNumber, QString occupation)
{
    qDebug() << "Salus: [Backend::addNewPatient()] - Adding new patient to database..." << "\n";
    patientsDb->addNewPatient(fullName, age, sex, birthDate, address, phoneNumber,  occupation);

    setPatient(fullName);

    emit patientAdded();
}

/**
 * @brief Добавляет новую запись текущего пациента
 * @param date
 * @param anamnesis
 * @param complaints
 * @param diseases
 * @param diagnosis
 * @param treatment
 * @return
 */
bool Backend::addNewRecord(QString date, QString anamnesis, QString complaints, QString diseases, QString diagnosis, QString treatment)
{
    if (patientsDb->addNewRecord(currentPatientBirthDate, date, anamnesis, complaints, diseases, diagnosis, treatment) == true)
    {
        patientRecordsListModel->setStringList(getCurrentPatientRecords());
        emit recordAdded();
        return true;
    }
    return false;
}

/**
 * @brief Удаляет выбранного пациента из БД.
 */
void Backend::deletePatient()
{
    if (!patientsDb->patientsList->isEmpty() == true)
        return;

    qDebug() << "Salus: [Backend::deletePatient()] - Deleting patient " << getCurrentDoctorFullName() << "...\n";
    patientsDb->deletePatient(currentPatientBirthDate);
    patientsDb->updateDbToFile();
    emit patientDeleted();
    qDebug() << "Salus: [Backend::deletePatient()] - Patient deleted from DB\n";
}

void Backend::setCurrentDoctorInn(quint16 inn)
{
    currentDoctorInn = inn;
}

bool Backend::getIsDoctorDbExists()
{
    qDebug() << "Salus: [Backend::getIsDoctorDbExists()] - returned " << doctorDb.doctorsList->isEmpty() << "\n";
    return doctorDb.doctorsList->isEmpty();
}

bool Backend::getIsPatientDbEmpty()
{
    return patientsDb->patientsList->isEmpty();
}

QString Backend::getCurrentDoctorFullName()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorFullName()] - returned " << doctorDb.getFullName(currentDoctorInn) << "\n";
    return doctorDb.getFullName(currentDoctorInn);
}

QString Backend::getCurrentDoctorSpecialization()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorSpecialization()] - returned " << doctorDb.getSpecialization(currentDoctorInn) << "\n";
    return doctorDb.getSpecialization(currentDoctorInn);
}

QString Backend::getCurrentDoctorInstitutionName()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorInsitutionName()] - returned " << doctorDb.getInstitutionName(currentDoctorInn) << "\n";
    return doctorDb.getInstitutionName(currentDoctorInn);
}

quint16 Backend::getCurrentDoctorInstitutionCode()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorInstitutionCode()] - returned " << doctorDb.getInstitutionCode(currentDoctorInn) << "\n";
    return doctorDb.getInstitutionCode(currentDoctorInn);
}

QString Backend::getCurrentDoctorInstitutionAddress()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorInsitutionAddress()] - returned " << doctorDb.getInstitutionAddress(currentDoctorInn) << "\n";
    return doctorDb.getInstitutionAddress(currentDoctorInn);
}

quint16 Backend::getCurrentDoctorInn()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorInn()] - returned " << currentDoctorInn << "\n";
    return currentDoctorInn;
}

QString Backend::getCurrentDoctorLicenseInfo()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorLicenseInfo()] - returned " << doctorDb.getLicenseInfo(currentDoctorInn) << "\n";
    return doctorDb.getLicenseInfo(currentDoctorInn);
}

QString Backend::getCurrentDoctorInitials()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorInitials()] - returned " << doctorDb.getProfileInitials(currentDoctorInn) << "\n";
    return doctorDb.getProfileInitials(currentDoctorInn);
}

quint16 Backend::getCurrentPatientAge()
{
    return patientsDb->getAge(currentPatientBirthDate);
}

bool Backend::getCurrentPatientSex()
{
    return patientsDb->getSex(currentPatientBirthDate);
}

QString Backend::getCurrentPatientFullName()
{
    return patientsDb->getFullName(currentPatientBirthDate);
}

QString Backend::getCurrentPatientBirthDate()
{
    return patientsDb->getBirthDate(currentPatientBirthDate);
}

QString Backend::getCurrentPatientPhoneNumber()
{
    return patientsDb->getPhoneNumber(currentPatientBirthDate);
}

QString Backend::getCurrentPatientAddress()
{
    return patientsDb->getAddress(currentPatientBirthDate);
}

QString Backend::getCurrentPatientOccupation()
{
    return patientsDb->getOccupation(currentPatientBirthDate);
}

QStringList Backend::getCurrentPatientRecords()
{
    return patientsDb->getRecordsList(currentPatientBirthDate);
}

QString Backend::getRecordAnamnesis(QString recordDate)
{
    return patientsDb->getAnamnesis(currentPatientBirthDate, recordDate);
}

QString Backend::getRecordComplaints(QString recordDate)
{
    return patientsDb->getComplaints(currentPatientBirthDate, recordDate);
}

QString Backend::getRecordDiagnosis(QString recordDate)
{
    return patientsDb->getDiagnosis(currentPatientBirthDate, recordDate);
}

QString Backend::getRecordDiseases(QString recordDate)
{
    return patientsDb->getDiseases(currentPatientBirthDate, recordDate);
}

QString Backend::getRecordTreatment(QString recordDate)
{
    return patientsDb->getTreatment(currentPatientBirthDate, recordDate);
}
