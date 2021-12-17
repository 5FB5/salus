#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    // Check for profiles on startup
    if (doctorDb.doctorsList->size() > 0) {
        if (doctorDb.doctorsList->size() == 1) {
            currentDoctorInn = doctorDb.getInn(); //FIXME: сейчас это работает только для одного профиля в БД
        }
    }
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

QList<QString> Backend::getPatientListNames()
{
    QList<QString> names;
    QList<Patient> list = *patientsDb.patientsList;

    foreach(Patient p, list) {
        names.append(p.fullName);
    }
    return names;
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

QString Backend::getCurrentPatientDiagnosis()
{
    return patientsDb.getDiagnosis(currentPatientBirthDate);
}

QString Backend::getCurrentPatientAnamnesis()
{
    return patientsDb.getAnamnesis(currentPatientBirthDate);
}

QList<QString> Backend::getCurrentPatientComplaints()
{
    return patientsDb.getComplaintsList(currentPatientBirthDate);
}

QList<QString> Backend::getCurrentPatientDiseases()
{
    return patientsDb.getDiseasesList(currentPatientBirthDate);
}

bool Backend::getIsDoctorDbExists()
{
    qDebug() << "Salus: [Backend::getIsDoctorDbExists()] - returned " << doctorDb.doctorsList->isEmpty() << "\n";
    return doctorDb.doctorsList->isEmpty();
}

void Backend::setCurrentDoctorInn(quint16 inn)
{
    currentDoctorInn = inn;
}

void Backend::setPatient(QString fullName)
{
    qDebug() << "Salus: [Backend::setPatient()] - Set patient " << fullName << "... \n";

    //FIXME: где-то не происходит обновление данных, из-за чего программа не может пробросить данные
    // поэтому мы гвоздями забиваем получение данных из файла
    // скорее всего это надо исправлять работу модели и способ получения и обновления данных
    patientsDb.getPatientsListFromJson();
    QList<Patient> patients = *patientsDb.patientsList;

    foreach(Patient p, patients) {
        if (p.fullName == fullName) {
            if (p.birthDate == currentPatientBirthDate) {
                qDebug() << "Salus: [Backend::setPatient()] - Patient birth date is the same with current! Return...\n";
                return;
            }
            else {
                qDebug() << "Salus: [Backend::setPatient()] - Select birth date " << p.birthDate << " of " << fullName << "...\n";
                currentPatientBirthDate = p.birthDate;
                qDebug() << "Salus: [Backend::setPatient()] - Birth date selected!\n";
                return;
            }
        }
    }

    qDebug() << "Salus: [Backend::setPatient()] - Current patient's birth date " << fullName << " is " << currentPatientBirthDate << "\n";
}

void Backend::addNewDoctorProfile(QString doctorFullName, QString doctorSpecialization,
                                  QString doctorInstitutionName, quint16 doctorInstitutionCode, QString doctorInstitutionAddress,
                                  quint16 doctorInn, QString doctorLicenseInfo)
{
    doctorDb.createNewProfile(doctorFullName, doctorSpecialization,
                              doctorInstitutionName,  doctorInstitutionCode,  doctorInstitutionAddress,
                              doctorInn,  doctorLicenseInfo);
}

void Backend::addNewPatient(QString fullName, quint16 age, bool sex,
                            QString birthDate, QString address,
                            QString phoneNumber, QString occupation)
{
    qDebug() << "Salus: [Backend::addNewPatient()] - Adding new patient to database..." << "\n";
    patientsDb.addNewPatient(fullName, age, sex, birthDate, address, phoneNumber,  occupation);

    qDebug() << "Salus: [Backend::addNewPatient()] Updated list is: ";
    foreach(Patient p, *patientsDb.patientsList) {
        qDebug() << "\t" << p.fullName;
    }

    setPatient(fullName);
}
