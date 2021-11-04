#include "backend.h"

Backend::Backend()
{
    QObject::connect(this, &Backend::setDoctorProfile, this, &Backend::selectProfile);
}

QString Backend::getCurrentDoctorInn()
{
    return currentDoctorInn;
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

void Backend::selectProfile(QString inn)
{
    currentDoctorInn = inn;
}
