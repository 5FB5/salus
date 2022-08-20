#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    // Проверка профиля на запуске
    if (doctorDb.doctorsList->size() > 0) {
        if (doctorDb.doctorsList->size() == 1) {
            currentDoctorInn = doctorDb.getInn();
        }
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

/*!
 *  \brief Добавление свойств и типов данных в контекст QML.
 *  \param context
 *  \warning Вызов должен происходить до загрузки движком URL
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

/*!
 *  \brief Устанавливает выбранного пациента по ФИО в качестве текущего.
 *  \param fullName ФИО пациента
*/
void Backend::setPatient(QString fullName)
{
    if (!patientsDb->patientsList->isEmpty()) {
        qDebug() << "Salus: [Backend::setPatient()] - Set patient " << fullName << "... \n";

        foreach(Patient p, *patientsDb->patientsList) {
            if (p.fullName == fullName) {
                if (p.birthDate == currentPatientBirthDate) {
                    qDebug() << "Salus: [Backend::setPatient()] - Patient birth date is the same with current! Return...\n";
                    return;
                }
                else {
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
}

/*!
 *  \brief Добавляет новый профиль врача в БД.
 *  \param doctorFullName ФИО врача
 *  \param doctorSpecialization Специализация
 *  \param doctorInstitutionName Название учреждения
 *  \param doctorInstitutionCode Код учреждения
 *  \param doctorInstitutionAddress Адрес учреждения
 *  \param doctorInn ИНН
 *  \param doctorLicenseInfo Номер лицензии
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

void Backend::updateRecord(QString recordDate, QString anamnesis, QString complaints, QString diseases, QString diagnosis, QString treatment)
{
    patientsDb->updateRecord(currentPatientBirthDate, recordDate, anamnesis, complaints,
                             diseases, diagnosis, treatment);
    emit recordUpdated();
}

void Backend::deleteRecord(QString recordDate)
{
    patientsDb->deleteRecord(currentPatientBirthDate, recordDate);
    patientsDb->updateDbToFile();
    patientRecordsListModel->setStringList(getCurrentPatientRecords());
    emit recordDeleted();
}

/*!
 *  \brief Добавляет нового пациента в БД
 *  \param fullName ФИО пациента
 *  \param age Возраст
 *  \param sex Пол
 *  \param birthDate Дата рождения
 *  \param address Адрес проживания
 *  \param phoneNumber Номер телефона
 *  \param occupation Профессия
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

/*!
 *  \brief Добавляет новую запись в список.
 *  Используется при внесении новой записи в карту текущего пациента в БД и для отображения записей в приложении
 *  \param date Дата записи
 *  \param anamnesis Анамнез
 *  \param complaints Жалобы
 *  \param diseases Перенесённые болезни
 *  \param diagnosis Текущий диагноз
 *  \param treatment Наименование лечения
*/
bool Backend::addNewRecord(QString date, QString anamnesis, QString complaints, QString diseases, QString diagnosis, QString treatment)
{
    if (patientsDb->addNewRecord(currentPatientBirthDate, date, anamnesis, complaints, diseases, diagnosis, treatment) == true) {
        patientRecordsListModel->setStringList(getCurrentPatientRecords());
        emit recordAdded();
        return true;
    }
    else {
        return false;
    }
    return false;
}

/*!
 *  \brief Удаляет выбранного пациента из БД.
*/
void Backend::deletePatient()
{
    if (!patientsDb->patientsList->isEmpty()) {
        qDebug() << "Salus: [Backend::deletePatient()] - Deleting patient " << getCurrentDoctorFullName() << "...\n";
        patientsDb->deletePatient(currentPatientBirthDate);
        patientsDb->updateDbToFile();
        emit patientDeleted();
        qDebug() << "Salus: [Backend::deletePatient()] - Patient deleted from DB\n";
    }
}

/*!
 *  \brief Устанавливает выбранного врача в качестве текущего по ИНН.
 *  \warning Данная функция неактуальна в использовании, так как предполагалась поддержка нескольких профилей врача в приложении
 *  \todo Удалить функцию со временем
*/
void Backend::setCurrentDoctorInn(quint16 inn)
{
    currentDoctorInn = inn;
}

/*!
 *  \return true, если БД профилей врача пустая.
*/
bool Backend::getIsDoctorDbExists()
{
    qDebug() << "Salus: [Backend::getIsDoctorDbExists()] - returned " << doctorDb.doctorsList->isEmpty() << "\n";
    return doctorDb.doctorsList->isEmpty();
}

/*!
 *  \return true, если БД пациентов пустая.
*/
bool Backend::getIsPatientDbEmpty()
{
    return patientsDb->patientsList->isEmpty();
}

/*!
 *  \return ФИО текущего врача.
*/
QString Backend::getCurrentDoctorFullName()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorFullName()] - returned " << doctorDb.getFullName(currentDoctorInn) << "\n";
    return doctorDb.getFullName(currentDoctorInn);
}

/*!
 *  \return Специализацию текущего врача.
*/
QString Backend::getCurrentDoctorSpecialization()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorSpecialization()] - returned " << doctorDb.getSpecialization(currentDoctorInn) << "\n";
    return doctorDb.getSpecialization(currentDoctorInn);
}

/*!
 *  \return Наименование учреждения текущего врача.
*/
QString Backend::getCurrentDoctorInstitutionName()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorInsitutionName()] - returned " << doctorDb.getInstitutionName(currentDoctorInn) << "\n";
    return doctorDb.getInstitutionName(currentDoctorInn);
}

/*!
 *  \return Код учреждения текущего врача.
*/
quint16 Backend::getCurrentDoctorInstitutionCode()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorInstitutionCode()] - returned " << doctorDb.getInstitutionCode(currentDoctorInn) << "\n";
    return doctorDb.getInstitutionCode(currentDoctorInn);
}

/*!
 *  \return Адрес учреждения текущего врача.
*/
QString Backend::getCurrentDoctorInstitutionAddress()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorInsitutionAddress()] - returned " << doctorDb.getInstitutionAddress(currentDoctorInn) << "\n";
    return doctorDb.getInstitutionAddress(currentDoctorInn);
}

/*!
 *  \return ИНН текущего врача.
*/
quint16 Backend::getCurrentDoctorInn()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorInn()] - returned " << currentDoctorInn << "\n";
    return currentDoctorInn;
}

/*!
 *  \return  номер лицензии текущего врача.
*/
QString Backend::getCurrentDoctorLicenseInfo()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorLicenseInfo()] - returned " << doctorDb.getLicenseInfo(currentDoctorInn) << "\n";
    return doctorDb.getLicenseInfo(currentDoctorInn);
}

/*!
 *  \return Инициалы текущего врача.
 *  \warning На данный момент не имеет реализации
*/
QString Backend::getCurrentDoctorInitials()
{
    qDebug() << "Salus: [Backend::getCurrentDoctorInitials()] - returned " << doctorDb.getProfileInitials(currentDoctorInn) << "\n";
    return doctorDb.getProfileInitials(currentDoctorInn);
}

/*!
 *  \return Возраст текущего пациента.
*/
quint16 Backend::getCurrentPatientAge()
{
    return patientsDb->getAge(currentPatientBirthDate);
}

/*!
 *  \return Пол текущего пациента.
*/
bool Backend::getCurrentPatientSex()
{
    return patientsDb->getSex(currentPatientBirthDate);
}

/*!
 *  \return ФИО текущего пациента.
*/
QString Backend::getCurrentPatientFullName()
{
    return patientsDb->getFullName(currentPatientBirthDate);
}

/*!
 *  \return Дату рождения текущего пациента.
*/
QString Backend::getCurrentPatientBirthDate()
{
    return patientsDb->getBirthDate(currentPatientBirthDate);
}

/*!
 *  \return Номер телефона текущего пациента.
*/
QString Backend::getCurrentPatientPhoneNumber()
{
    return patientsDb->getPhoneNumber(currentPatientBirthDate);
}

/*!
 *  \return Адрес проживания текущего пациента.
*/
QString Backend::getCurrentPatientAddress()
{
    return patientsDb->getAddress(currentPatientBirthDate);
}

/*!
 *  \return Профессию текущего пациента.
*/
QString Backend::getCurrentPatientOccupation()
{
    return patientsDb->getOccupation(currentPatientBirthDate);
}

/*!
 *  \return Записи амбулаторной карты текущего пациента.
*/
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

//QString Backend::getCurrentPatientDiagnosis()
//{
//    return patientsDb.getDiagnosis(currentPatientBirthDate);
//}

//QString Backend::getCurrentPatientAnamnesis()
//{
//    return patientsDb.getAnamnesis(currentPatientBirthDate);
//}

//QList<QString> Backend::getCurrentPatientComplaints()
//{
//    return patientsDb.getComplaintsList(currentPatientBirthDate);
//}

//QList<QString> Backend::getCurrentPatientDiseases()
//{
//    return patientsDb.getDiseasesList(currentPatientBirthDate);
//}
