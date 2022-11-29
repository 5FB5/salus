#ifndef BACKEND_H
#define BACKEND_H

#include "QtQml/qqml.h"
#include "QtQml/qqmlcontext.h"
#include <QStringListModel>
#include <QObject>
#include <QDebug>
#include <QString>

#include "doctor/doctordatabase.h"
#include "doctor/glossarydatabase.h"

#include "patient/patientdatabase.h"
#include "patient/patientlistmodel.h"

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
    GlossaryDatabase *glossaryDb;

    PatientDataBase *patientsDb;
    PatientListModel *patientListModel;

    QStringListModel *patientRecordsListModel;
    QStringListModel *glossaryDiagnosesListModel;
    QStringListModel *glossaryTreatmentsListModel;

public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();

    void addPropertiesToContext(QQmlContext *context);

    QString currentPatientBirthDate;

    quint16 currentDoctorInn;

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
    quint16 getCurrentPatientAge();

//    QString getCurrentPatientRecordDate();
//    QString getCurrentPatientRecordDiagnosis();
//    QString getCurrentPatientRecordAnamnesis();
//    QString getCurrentPatientRecordComplaints();
//    QString getCurrentPatientRecordDiseases();
//    QString getCurrentPatientRecordTreatment();

    bool getCurrentPatientSex();
    bool getIsDoctorDbExists();
    bool getIsPatientDbEmpty();

public slots:
    void addNewPatient(QString fullName, quint16 age, bool sex,
                       QString birthDate, QString address,
                       QString phoneNumber, QString occupation);

    void addNewDoctorProfile(QString doctorFullName, QString doctorSpecialization,
                             QString doctorInstitutionName, quint16 doctorInstitutionCode,
                             QString doctorInstitutionAddress, quint16 doctorInn,
                             QString doctorLicenseInfo);

    void deletePatient();

    void updateRecord(QString recordDate, QString anamnesis, QString complaints,
                      QString diseases, QString diagnosis, QString treatment);
    void deleteRecord(QString recordDate);

    void setCurrentDoctorInn(quint16 inn);
    void setPatient(QString fullName);

    bool addNewRecord(QString date, QString anamnesis, QString complaints,
                      QString diseases, QString diagnosis, QString treatment);

    void addGlossaryDiagnosis(QString data);
    void addGlossaryTreatment(QString data);
    void editGlossaryDiagnosis(QString oldData, QString newData);
    void editGlossaryTreatment(QString oldData, QString newData);
    void deleteGlossaryDiagnosis(QString data);
    void deleteGlossaryTreatment(QString data);

    QString getRecordAnamnesis(QString recordDate);
    QString getRecordComplaints(QString recordDate);
    QString getRecordDiagnosis(QString recordDate);
    QString getRecordDiseases(QString recordDate);
    QString getRecordTreatment(QString recordDate);

    QString getGlossaryDiagnosisAt(int index);
    QString getGlossaryTreatmentAt(int index);

    QStringList getCurrentPatientRecords();
    QStringList getGlossaryDiagnosesList();
    QStringList getGlossaryTreatmentsList();

signals:
    void profileAdded();
    void patientAdded();
    void patientDeleted();
    void recordAdded();
    void recordUpdated();
    void recordDeleted();
    void changeDoctorProfile();
    void glossaryDiagnosisAdded();
    void glossaryTreatmentAdded();
    void glossaryDiagnosisChanged();
    void glossaryTreatmentChanged();
    void glossaryDiagnosisDeleted();
    void glossaryTreatmentDeleted();
};

#endif // BACKEND_H
