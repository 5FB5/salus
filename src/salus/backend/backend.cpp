#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    // Проверка профиля на запуске
    if (doctorDb.doctorsList->size() > 0) {
        if (doctorDb.doctorsList->size() == 1) {
            currentDoctorInn = doctorDb.getInn();
        }
    }

    patientListModel = new PatientListModel;
    patientRecordsListModel = new PatientRecordsListModel;

    patientListModel->patientDb.patientsList = patientsDb.patientsList;
//    patientRecordsListModel->recordsList = getCurrentPatientRecords();

}

Backend::~Backend()
{
    qDebug() << "Salus: [Backend::~Backend] - updateDbToFile()\n";
    patientsDb.updateDbToFile();
    delete patientListModel;
}

void Backend::addPropertiesToContext(QQmlContext *context)
{
    qmlRegisterType<Backend>("salus", 1, 0, "Backend");
    context->setContextProperty("backend", this);

    qmlRegisterType<PatientListModel>("salus", 1, 0, "PatientListModel");
    context->setContextProperty("patientListModel", patientListModel);

    qmlRegisterType<PatientRecordsListModel>("salus", 1, 0, "PatientRecordsListModel");
    context->setContextProperty("patientRecordsListModel", patientRecordsListModel);
}

void Backend::setPatient(QString fullName)
{
    if (!patientsDb.patientsList->isEmpty()) {
        qDebug() << "Salus: [Backend::setPatient()] - Set patient " << fullName << "... \n";

        foreach(Patient p, *patientsDb.patientsList) {
            if (p.fullName == fullName) {
                if (p.birthDate == currentPatientBirthDate) {
                    qDebug() << "Salus: [Backend::setPatient()] - Patient birth date is the same with current! Return...\n";
                    return;
                }
                else {
                    qDebug() << "Salus: [Backend::setPatient()] - Select birth date " << p.birthDate << " of " << fullName << "...\n";
                    currentPatientBirthDate = p.birthDate;
                    patientRecordsListModel->recordsList = getCurrentPatientRecords();
                    qDebug() << "Salus: [Backend::setPatient()] - Birth date selected!\n";
                    return;
                }
            }
        }
        qDebug() << "Salus: [Backend::setPatient()] - Current patient's birth date " << fullName << " is " << currentPatientBirthDate << "\n";
    }
}

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

void Backend::addNewPatient(QString fullName, quint16 age, bool sex,
                            QString birthDate, QString address,
                            QString phoneNumber, QString occupation)
{
    qDebug() << "Salus: [Backend::addNewPatient()] - Adding new patient to database..." << "\n";
    patientsDb.addNewPatient(fullName, age, sex, birthDate, address, phoneNumber,  occupation);

    setPatient(fullName);

    emit patientAdded();
}

void Backend::deletePatient()
{
    if (!patientsDb.patientsList->isEmpty()) {
        qDebug() << "Salus: [Backend::deletePatient()] - Deleting patient " << getCurrentDoctorFullName() << "...\n";
        patientsDb.deletePatient(currentPatientBirthDate);
        patientsDb.updateDbToFile();
        emit patientDeleted();
        qDebug() << "Salus: [Backend::deletePatient()] - Patient deleted from DB\n";
    }
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
    return patientsDb.patientsList->isEmpty();
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
    return patientsDb.getAge(currentPatientBirthDate);
}

bool Backend::getCurrentPatientSex()
{
    return patientsDb.getSex(currentPatientBirthDate);
}

QString Backend::getCurrentPatientFullName()
{
    return patientsDb.getFullName(currentPatientBirthDate);
}

QString Backend::getCurrentPatientBirthDate()
{
    return patientsDb.getBirthDate(currentPatientBirthDate);
}

QString Backend::getCurrentPatientPhoneNumber()
{
    return patientsDb.getPhoneNumber(currentPatientBirthDate);
}

QString Backend::getCurrentPatientAddress()
{
    return patientsDb.getAddress(currentPatientBirthDate);
}

QString Backend::getCurrentPatientOccupation()
{
    return patientsDb.getOccupation(currentPatientBirthDate);
}

QList<Record_t> Backend::getCurrentPatientRecords()
{
    return patientsDb.getRecordsList(currentPatientBirthDate);
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
