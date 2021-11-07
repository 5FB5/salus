#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    QObject::connect(this, &Backend::setDoctorProfile, this, &Backend::selectDoctorProfile);
}

/*
 * Interface for working with Doctors database
 */

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

void Backend::selectDoctorProfile(QString inn)
{
    currentDoctorInn = inn;
}
