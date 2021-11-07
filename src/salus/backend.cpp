#include "backend.h"



Backend::Backend()
Backend::Backend(QObject *parent) : QObject(parent)
{
    QObject::connect(this, &Backend::setDoctorProfile, this, &Backend::selectProfile);
    QObject::connect(this, &Backend::setPatientProfile, this, &Backend::selectPatientProfile);
}

QString Backend::getCurrentDoctorInn()
{
    return currentDoctorInn;
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

void Backend::selectProfile(QString inn)
{
    currentDoctorInn = inn;
}
QString Backend::getCurrentPatientInsuranceNumber(){
    return currentPatientInsuranceNumber;
}
void Backend::selectPatientProfile(QString insuranceNumber)
{
    currentPatientInsuranceNumber = insuranceNumber;
}
