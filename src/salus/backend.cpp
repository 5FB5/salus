#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    // Check for profiles on startup
    if (doctorDb.doctorsList->size() > 0) {
        if (doctorDb.doctorsList->size() == 1) {
            currentDoctorInn = doctorDb.getInn(); //FIXME: this works only for 1 profile in database
        }
    }
}

QString Backend::getCurrentDoctorFullName()
{
    return doctorDb.getFullName(currentDoctorInn);
}

QString Backend::getCurrentDoctorSpecialization()
{
    return doctorDb.getSpecialization(currentDoctorInn);
}

QString Backend::getCurrentDoctorInstitutionName()
{
    return doctorDb.getInstitutionName(currentDoctorInn);
}

QString Backend::getCurrentDoctorInstitutionCode()
{
    return doctorDb.getInstitutionCode(currentDoctorInn);
}

QString Backend::getCurrentDoctorInstitutionAddress()
{
    return doctorDb.getInstitutionAddress(currentDoctorInn);
}

QString Backend::getCurrentDoctorInn()
{
    return currentDoctorInn;
}

void Backend::setCurrentDoctorInn(QString inn)
{
    currentDoctorInn = inn;
}

QString Backend::getCurrentDoctorLicenseInfo()
{
    return doctorDb.getLicenseInfo(currentDoctorInn);
}

QString Backend::getCurrentDoctorInitials()
{
    return doctorDb.getProfileInitials(currentDoctorInn);
}

bool Backend::getIsDoctorDbExists()
{
    return doctorDb.doctorsList->isEmpty();
}

void Backend::addNewDoctorProfile(QString doctorFullName, QString doctorSpecialization,
                                  QString doctorInstitutionName, QString doctorInstitutionCode, QString doctorInstitutionAddress,
                                  QString doctorInn, QString doctorLicenseInfo)
{
    doctorDb.createNewProfile(doctorFullName, doctorSpecialization,
                              doctorInstitutionName,  doctorInstitutionCode,  doctorInstitutionAddress,
                              doctorInn,  doctorLicenseInfo);
    emit setDoctorProfile(doctorInn);
}
void Backend::addNewPatient(QString fullName, quint8 age,
                            bool sex,
                            QDate birthDate,
                            QString adress,
                            QString insuranceCompany,
                            QString insuranceNumber,
                            QString phoneNumber,
                            QString occupation,
                            QString diagnosis,
                            QList<QString> diseases,
                            QString diseaseDescription)
{
    patient.addNewPatient(fullName, age, sex,  birthDate,  adress, insuranceCompany,
                            insuranceNumber,phoneNumber,occupation,diagnosis,diseases,diseaseDescription);

    emit setPatientProfile(insuranceNumber);
}

    currentDoctorInn = doctorInn;
}
QString Backend::getCurrentPatientInsuranceNumber(){
    return currentPatientInsuranceNumber;
}
void Backend::selectPatientProfile(QString insuranceNumber)
{
    currentPatientInsuranceNumber = insuranceNumber;
}
