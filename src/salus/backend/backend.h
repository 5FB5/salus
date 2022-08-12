#ifndef BACKEND_H
#define BACKEND_H

#include "QtQml/qqml.h"
#include "QtQml/qqmlcontext.h"
#include <QStringListModel>
#include <QObject>
#include <QDebug>
#include <QString>

#include "doctor/doctordatabase.h"
#include "patient/patientdatabase.h"
#include "patient/patientlistmodel.h"

/*!
 * \brief Backend класс для работы с frontend частью приложения
 */
class Backend : public QObject
{
    Q_OBJECT

    // Свойства для получения данных текущего выбранного врача из QML
    Q_PROPERTY(QString currentDoctorFullName READ getCurrentDoctorFullName) // WRITE setCurrentDoctorFullname)
    Q_PROPERTY(QString currentDoctorSpecialization READ getCurrentDoctorSpecialization) // WRITE setCurrentDoctorSpecialization)
    Q_PROPERTY(QString currentDoctorInstitutionName READ getCurrentDoctorInstitutionName) // WRITE setCurrentDoctorInstitutionName)
    Q_PROPERTY(QString currentDoctorInstitutionAddress READ getCurrentDoctorInstitutionAddress) // WRITE setCurrentDoctorInstitutionAddress)
    Q_PROPERTY(QString currentDoctorLicenseInfo READ getCurrentDoctorLicenseInfo) // WRITE setCurrentDoctorLicenseInfo)
    Q_PROPERTY(QString currentDoctorInitials READ getCurrentDoctorInitials)
    Q_PROPERTY(quint16 currentDoctorInstitutionCode READ getCurrentDoctorInstitutionCode) // WRITE setCurrentDoctorInstitutionCode)
    Q_PROPERTY(quint16 currentDoctorInn READ getCurrentDoctorInn) // WRITE setCurrentDoctorInn)

    Q_PROPERTY(bool isDoctorDbEmpty READ getIsDoctorDbExists)
    Q_PROPERTY(bool isPatientDbEmpty READ getIsPatientDbEmpty)

    Q_PROPERTY(QString currentPatientFullName READ getCurrentPatientFullName);
    Q_PROPERTY(quint16 currentPatientAge READ getCurrentPatientAge);
    Q_PROPERTY(bool currentPatientSex READ getCurrentPatientSex);
    Q_PROPERTY(QString currentPatientBirthDate READ getCurrentPatientBirthDate); // используется как первичный ключ
    Q_PROPERTY(QString currentPatientAddress READ getCurrentPatientAddress);
    Q_PROPERTY(QString currentPatientOccupation READ getCurrentPatientOccupation);
    Q_PROPERTY(QString currentPatientPhoneNumber READ getCurrentPatientPhoneNumber);

private:
    DoctorDataBase doctorDb;

    PatientDataBase *patientsDb;

    PatientListModel *patientListModel;

    QStringListModel *patientRecordsListModel;

public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();

    void addPropertiesToContext(QQmlContext *context);

    /*!
     *  @brief Хранит значение ИНН текущего профиля врача.
     *  Используется как первичный ключ для доступа к остальным данным
    */
    quint16 currentDoctorInn;

    /*!
     *  @brief Хранит дату рождения текущего пациента.
     *  Используется как первичный ключ для доступа к остальным данным
    */
    QString currentPatientBirthDate;

    quint16 getCurrentDoctorInstitutionCode();
    quint16 getCurrentDoctorInn();

    QString getCurrentDoctorFullName();
    QString getCurrentDoctorSpecialization();
    QString getCurrentDoctorInstitutionName();
    QString getCurrentDoctorInstitutionAddress();
    QString getCurrentDoctorLicenseInfo();
    QString getCurrentDoctorInitials();

    QString getCurrentPatientFullName();
    QString getCurrentPatientBirthDate();
    QString getCurrentPatientPhoneNumber();
    QString getCurrentPatientAddress();
    QString getCurrentPatientOccupation();
//    QString getCurrentPatientRecordDate();
//    QString getCurrentPatientRecordDiagnosis();
//    QString getCurrentPatientRecordAnamnesis();
//    QString getCurrentPatientRecordComplaints();
//    QString getCurrentPatientRecordDiseases();
//    QString getCurrentPatientRecordTreatment();

    quint16 getCurrentPatientAge();

    bool getCurrentPatientSex();

    bool getIsDoctorDbExists();

    bool getIsPatientDbEmpty();

public slots:
    void addNewPatient(QString fullName, quint16 age, bool sex,
                       QString birthDate, QString address,
                       QString phoneNumber, QString occupation);

    void addNewRecord(QString date, QString anamnesis, QString complaints,
                      QString diseases, QString diagnosis, QString treatment);

    void deletePatient();

    void addNewDoctorProfile(QString doctorFullName, QString doctorSpecialization,
                             QString doctorInstitutionName, quint16 doctorInstitutionCode,
                             QString doctorInstitutionAddress, quint16 doctorInn,
                             QString doctorLicenseInfo);

    void setCurrentDoctorInn(quint16 inn);

    void setPatient(QString fullName);

    QStringList getCurrentPatientRecords();

    QString getRecordAnamnesis(QString recordDate);
    QString getRecordComplaints(QString recordDate);
    QString getRecordDiagnosis(QString recordDate);
    QString getRecordDiseases(QString recordDate);
    QString getRecordTreatment(QString recordDate);

signals:
    void profileAdded();
    void patientAdded();
    void patientDeleted();
    void recordAdded();
    void changeDoctorProfile();

};


#endif // BACKEND_H
