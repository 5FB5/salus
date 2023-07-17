#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    // Проверка профиля на запуске
    if (doctorDb.doctorsList->size() > 0)
    {
        if (doctorDb.doctorsList->size() == 1)
            currentDoctorInn = doctorDb.getInn();
    }

    glossaryDb = new GlossaryDatabase;
    patientsDb = new PatientDataBase;

    patientListModel = new PatientListModel;
    patientRecordsListModel = new QStringListModel();

    glossaryDiagnosesListModel = new QStringListModel();
    glossaryTreatmentsListModel = new QStringListModel();
    glossarySymptomsListModel = new QStringListModel();
    glossaryUserListModel = new QStringListModel();

    glossaryDiagnosesFilteredListModel = new QStringListModel();
    glossaryTreatmentsFilteredListModel = new QStringListModel();
    glossarySymptomsFilteredListModel = new QStringListModel();
    glossaryUserFilteredListModel = new QStringListModel();

    patientListModel->patientDb.patientsList = patientsDb->patientsList;
    patientRecordsListModel->setStringList(getCurrentPatientRecords());
    sortPatientRecordListModel();

    glossaryDiagnosesListModel->setStringList(getGlossaryDiagnosesList());
    glossaryTreatmentsListModel->setStringList(getGlossaryTreatmentsList());
    glossarySymptomsListModel->setStringList(getGlossarySymptomsList());
    glossaryUserListModel->setStringList(getGlossaryUserList());
}

Backend::~Backend()
{
    qDebug() << "[Backend::~Backend] - updateDbToFile()\n";
    patientsDb->updateDbToFile();

    delete patientListModel;
    delete patientRecordsListModel;
    delete patientsDb;

    delete glossaryDiagnosesFilteredListModel;
    delete glossaryTreatmentsFilteredListModel;
    delete glossarySymptomsFilteredListModel;
    delete glossaryUserFilteredListModel;

    delete glossaryDiagnosesListModel;
    delete glossaryTreatmentsListModel;
    delete glossarySymptomsListModel;
    delete glossaryUserListModel;
    delete glossaryDb;
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
    context->setContextProperty("patientRecordsListModel", patientRecordsListModel);

    context->setContextProperty("glossaryDiagnosesListModel", glossaryDiagnosesListModel);
    context->setContextProperty("glossaryTreatmentsListModel", glossaryTreatmentsListModel);
    context->setContextProperty("glossarySymptomsListModel", glossarySymptomsListModel);
    context->setContextProperty("glossaryUserListModel", glossaryUserListModel);

    context->setContextProperty("glossaryDiagnosesFilteredListModel", glossaryDiagnosesFilteredListModel);
    context->setContextProperty("glossaryTreatmentsFilteredListModel", glossaryTreatmentsFilteredListModel);
    context->setContextProperty("glossarySymptomsFilteredListModel", glossarySymptomsFilteredListModel);
    context->setContextProperty("glossaryUserFilteredListModel", glossaryUserFilteredListModel);
}

void Backend::setPatient(QString fullName)
{
    if (patientsDb->patientsList->isEmpty() == true)
        return;

    qDebug() << "[Backend::setPatient()] - Set patient " << fullName << "... \n";

    foreach(Patient p, *patientsDb->patientsList)
    {
        if (p.fullName == fullName)
        {
            if (p.birthDate == currentPatientBirthDate)
            {
                qDebug() << "[Backend::setPatient()] - Patient birth date is the same with current! Return...\n";
                return;
            }
            else
            {
                qDebug() << "[Backend::setPatient()] - Select birth date " << p.birthDate << " of " << fullName << "...\n";
                currentPatientBirthDate = p.birthDate;
                patientRecordsListModel->setStringList(getCurrentPatientRecords());
                sortPatientRecordListModel();
                qDebug() << "[Backend::setPatient()] - Birth date selected!\n";
                return;
            }
        }
    }
    qDebug() << "[Backend::setPatient()] - Current patient's birth date " << fullName << " is " << currentPatientBirthDate << "\n";
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
void Backend::updateRecord(QString recordDate, QString anamnesis, QString complaints, QString diseases, QString diagnosis, QString treatment, QString treatmentResult)
{
    patientsDb->updateRecord(currentPatientBirthDate, recordDate, anamnesis, complaints,
                             diseases, diagnosis, treatment, treatmentResult);
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
    sortPatientRecordListModel();
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
void Backend::addNewPatient(QString fullName, int age, bool sex,
                            QString birthDate, QString address,
                            QString phoneNumber, QString occupation)
{
    qDebug() << "[Backend::addNewPatient()] - Adding new patient to database..." << "\n";
    patientsDb->addNewPatient(fullName, age, sex, birthDate, address, phoneNumber,  occupation);
    setPatient(fullName);

    emit patientAdded();
    patientsDb->updateDbToFile();
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
bool Backend::addNewRecord(QString date, QString anamnesis, QString complaints, QString diseases, QString diagnosis, QString treatment, QString treatmentResult)
{
    if (patientsDb->addNewRecord(currentPatientBirthDate, date, anamnesis, complaints, diseases, diagnosis, treatment, treatmentResult) == true)
    {
        patientRecordsListModel->setStringList(getCurrentPatientRecords());
        sortPatientRecordListModel();
        emit recordAdded();
        patientsDb->updateDbToFile();
        return true;
    }
    return false;
}

void Backend::addGlossaryDiagnosis(QString data)
{
    if (glossaryDb == nullptr)
        return;

    glossaryDb->addDataToDiagnosesList(data);
    glossaryDiagnosesListModel->setStringList(getGlossaryDiagnosesList());

    emit glossaryDiagnosisAdded();
}

void Backend::addGlossaryTreatment(QString data)
{
    if (glossaryDb == nullptr)
        return;

    glossaryDb->addDataToTreatmentsList(data);
    glossaryTreatmentsListModel->setStringList(getGlossaryTreatmentsList());

    emit glossaryTreatmentAdded();
}

void Backend::editGlossaryDiagnosis(QString oldData, QString newData)
{
    if (glossaryDb == nullptr || oldData == "")
        return;

    glossaryDb->editDiagnosis(oldData, newData);
    glossaryDiagnosesListModel->setStringList(getGlossaryDiagnosesList());

    emit glossaryDiagnosisChanged();
}

void Backend::editGlossaryTreatment(QString oldData, QString newData)
{
    if (glossaryDb == nullptr || oldData == "")
        return;

    glossaryDb->editTreatment(oldData, newData);
    glossaryTreatmentsListModel->setStringList(getGlossaryTreatmentsList());

    emit glossaryTreatmentChanged();
}

void Backend::editGlossarySymptom(QString oldData, QString newData)
{
    if (glossaryDb == nullptr || oldData == "")
        return;

    glossaryDb->editSymptom(oldData, newData);
    glossarySymptomsListModel->setStringList(getGlossarySymptomsList());

    emit glossarySymptomChanged();
}

void Backend::editGlossaryUserFormulation(QString oldData, QString newData)
{
    if (glossaryDb == nullptr || oldData == "")
        return;

    glossaryDb->editUserListItem(oldData, newData);
    glossaryUserListModel->setStringList(getGlossaryUserList());

    emit glossaryUserFormulationChanged();
}

void Backend::addGlossarySymptom(QString data)
{
    if (glossaryDb == nullptr)
        return;

    glossaryDb->addDataToSymptomsList(data);
    glossarySymptomsListModel->setStringList(getGlossarySymptomsList());

    emit glossarySymptomAdded();
}

void Backend::addGlossaryUserFormulation(QString data)
{
    if (glossaryDb == nullptr)
        return;

    glossaryDb->addDataToUserList(data);
    glossaryUserListModel->setStringList(getGlossaryUserList());

    emit glossaryUserFormulationAdded();
}

void Backend::deleteGlossaryDiagnosis(QString data)
{
    if (glossaryDb == nullptr || data == "")
        return;

    glossaryDb->deleteDiagnosis(data);
    glossaryDiagnosesListModel->setStringList(getGlossaryDiagnosesList());

    emit glossaryDiagnosisDeleted();
}

void Backend::deleteGlossaryTreatment(QString data)
{
    if (glossaryDb == nullptr || data == "")
        return;

    glossaryDb->deleteTreatment(data);
    glossaryTreatmentsListModel->setStringList(getGlossaryTreatmentsList());

    emit glossaryTreatmentDeleted();
}

void Backend::deleteGlossarySymptom(QString data)
{
    if (glossaryDb == nullptr || data == "")
        return;

    glossaryDb->deleteSymptom(data);
    glossarySymptomsListModel->setStringList(getGlossarySymptomsList());

    emit glossarySymptomDeleted();
}

void Backend::deleteGlossaryUserFormulation(QString data)
{
    if (glossaryDb == nullptr || data == "")
        return;

    glossaryDb->deleteUserListItem(data);
    glossaryUserListModel->setStringList(getGlossaryUserList());

    emit glossaryUserFormulationDeleted();
}

/**
 * @brief Удаляет выбранного пациента из БД.
 */
void Backend::deletePatient()
{
    if (patientsDb->patientsList->isEmpty() == true)
        return;

    qDebug() << "[Backend::deletePatient()] - Deleting patient " << getCurrentDoctorFullName() << "...\n";
    patientsDb->deletePatient(currentPatientBirthDate);
    patientsDb->updateDbToFile();
    emit patientDeleted();
    qDebug() << "[Backend::deletePatient()] - Patient deleted from DB\n";
}

void Backend::setCurrentDoctorInn(quint16 inn)
{
    currentDoctorInn = inn;
}

bool Backend::getIsDoctorDbExists()
{
    qDebug() << "[Backend::getIsDoctorDbExists()] - returned " << doctorDb.doctorsList->isEmpty() << "\n";
    return doctorDb.doctorsList->isEmpty();
}

bool Backend::getIsPatientDbEmpty()
{
    return patientsDb->patientsList->isEmpty();
}

void Backend::printCard()
{
    patientsDb->saveCardPdf(currentPatientBirthDate);
}

void Backend::printCard(int pageNumber, bool fillPatientData)
{
    patientsDb->saveCardPdf(currentPatientBirthDate, pageNumber, fillPatientData);
}

void Backend::printDiary(QString recordDate)
{
    patientsDb->saveDiaryPdf(currentPatientBirthDate, recordDate);
}

void Backend::sortPatientRecordListModel()
{
    if (patientRecordsListModel == nullptr)
        return;

    QList<QDate> dates;

    for (const auto &it : patientRecordsListModel->stringList())
    {
        QDate currentDate = QDate::fromString(it, "dd.MM.yyyy");
        dates.push_back(currentDate);
    }

    std::sort(std::begin(dates), std::end(dates));

    QStringList sortedList;

    for (const auto &it : dates)
    {
        sortedList.push_back(it.toString("dd.MM.yyyy"));
    }

    patientRecordsListModel->setStringList(sortedList);
}

QString Backend::getCurrentDoctorFullName()
{
    qDebug() << "[Backend::getCurrentDoctorFullName()] - returned " << doctorDb.getFullName(currentDoctorInn) << "\n";
    return doctorDb.getFullName(currentDoctorInn);
}

QString Backend::getCurrentDoctorSpecialization()
{
    qDebug() << "[Backend::getCurrentDoctorSpecialization()] - returned " << doctorDb.getSpecialization(currentDoctorInn) << "\n";
    return doctorDb.getSpecialization(currentDoctorInn);
}

QString Backend::getCurrentDoctorInstitutionName()
{
    qDebug() << "[Backend::getCurrentDoctorInsitutionName()] - returned " << doctorDb.getInstitutionName(currentDoctorInn) << "\n";
    return doctorDb.getInstitutionName(currentDoctorInn);
}

quint16 Backend::getCurrentDoctorInstitutionCode()
{
    qDebug() << "[Backend::getCurrentDoctorInstitutionCode()] - returned " << doctorDb.getInstitutionCode(currentDoctorInn) << "\n";
    return doctorDb.getInstitutionCode(currentDoctorInn);
}

QString Backend::getCurrentDoctorInstitutionAddress()
{
    qDebug() << "[Backend::getCurrentDoctorInsitutionAddress()] - returned " << doctorDb.getInstitutionAddress(currentDoctorInn) << "\n";
    return doctorDb.getInstitutionAddress(currentDoctorInn);
}

quint16 Backend::getCurrentDoctorInn()
{
    qDebug() << "[Backend::getCurrentDoctorInn()] - returned " << currentDoctorInn << "\n";
    return currentDoctorInn;
}

QString Backend::getCurrentDoctorLicenseInfo()
{
    qDebug() << "[Backend::getCurrentDoctorLicenseInfo()] - returned " << doctorDb.getLicenseInfo(currentDoctorInn) << "\n";
    return doctorDb.getLicenseInfo(currentDoctorInn);
}

QString Backend::getCurrentDoctorInitials()
{
    qDebug() << "[Backend::getCurrentDoctorInitials()] - returned " << doctorDb.getProfileInitials(currentDoctorInn) << "\n";
    return doctorDb.getProfileInitials(currentDoctorInn);
}

int Backend::getCurrentPatientAge()
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

QStringList Backend::getGlossaryDiagnosesList()
{
    return glossaryDb->getDiagnosesListModel();
}

QStringList Backend::getGlossaryTreatmentsList()
{
    return glossaryDb->getTreatmentsListModel();
}

QStringList Backend::getGlossarySymptomsList()
{
    return glossaryDb->getSymptomsListModel();
}

QStringList Backend::getGlossaryUserList()
{
    return glossaryDb->getUserListModel();
}

void Backend::getGlossaryDiagnosesByName(QString name)
{
    QStringList list = getGlossaryDiagnosesList();
    QStringList filteredList = list.filter(QRegularExpression(name, QRegularExpression::CaseInsensitiveOption | QRegularExpression::DotMatchesEverythingOption));

    glossaryDiagnosesFilteredListModel->setStringList(filteredList);
}

void Backend::getGlossaryTreatmentsByName(QString name)
{
    QStringList list = getGlossaryTreatmentsList();
    QStringList filteredList = list.filter(QRegularExpression(name, QRegularExpression::CaseInsensitiveOption | QRegularExpression::DotMatchesEverythingOption));

    glossaryTreatmentsFilteredListModel->setStringList(filteredList);
}

void Backend::getGlossarySymptomsByName(QString name)
{
    QStringList list = getGlossarySymptomsList();
    QStringList filteredList = list.filter(QRegularExpression(name, QRegularExpression::CaseInsensitiveOption | QRegularExpression::DotMatchesEverythingOption));

    glossarySymptomsFilteredListModel->setStringList(filteredList);
}

void Backend::getGlossaryUserListByName(QString name)
{
    QStringList list = getGlossaryUserList();
    QStringList filteredList = list.filter(QRegularExpression(name, QRegularExpression::CaseInsensitiveOption | QRegularExpression::DotMatchesEverythingOption));

    glossaryUserFilteredListModel->setStringList(filteredList);
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

QString Backend::getRecordTreatmentResult(QString recordDate)
{
    return patientsDb->getTreatmentResult(currentPatientBirthDate, recordDate);
}

QString Backend::getGlossaryDiagnosisAt(int index)
{
    return glossaryDb->getDiagnosisAt(index);
}

QString Backend::getGlossaryTreatmentAt(int index)
{
    return glossaryDb->getTreatmentAt(index);
}

QString Backend::getGlossarySymptomAt(int index)
{
    return glossaryDb->getSymptomAt(index);
}

QString Backend::getGlossaryUserFormulationAt(int index)
{
    return glossaryDb->getUserItemAt(index);
}
