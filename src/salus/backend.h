#ifndef BACKEND_H
#define BACKEND_H

#include <QString>
#include <QObject>

#include "doctordatabase.h"
#include "patientdatabase.h"

/*! Класс для работы с QML фронтендом. Объединяет интерфейсы БД врача и пациентов */
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

    Q_PROPERTY(QList<QString> patientListNames READ getPatientListNames);

    Q_PROPERTY(QString currentPatientFullName READ getCurrentPatientFullName);
    Q_PROPERTY(quint16 currentPatientAge READ getCurrentPatientAge);
    Q_PROPERTY(bool currentPatientSex READ getCurrentPatientSex);
    Q_PROPERTY(QString currentPatientBirthDate READ getCurrentPatientBirthDate); // используется как первичный ключ
    Q_PROPERTY(QString currentPatientAddress READ getCurrentPatientAddress);
    Q_PROPERTY(QString currentPatientOccupation READ getCurrentPatientOccupation);
    Q_PROPERTY(QString currentPatientDiagnosis READ getCurrentPatientDiagnosis);
    Q_PROPERTY(QList<QString> currentPatientComplaints READ getCurrentPatientComplaints);
    Q_PROPERTY(QString currentPatientAnamnesis READ getCurrentPatientAnamnesis);
    Q_PROPERTY(QList<QString> currentPatientDiseases READ getCurrentPatientDiseases);


public:
    explicit Backend(QObject *parent = nullptr);

    /*! Глобальный класс для доступа к БД врача */
    DoctorDataBase doctorDb;
    /*! Глобальный класс для доступа к БД пациента */
    PatientDataBase patientsDb;

    /*!
     *  Хранит значение ИНН текущего профиля врача.
     *  Используется как первичный ключ для доступа к остальным данным
    */
    quint16 currentDoctorInn;
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
    QString getCurrentPatientAddress();
    QString getCurrentPatientOccupation();
    QString getCurrentPatientDiagnosis();
    QString getCurrentPatientAnamnesis();
    QList<QString> getCurrentPatientComplaints();
    QList<QString> getCurrentPatientDiseases();
    QList<QString> getPatientListNames(); // Используется для отображения имён в выпадающем списке в QML
    quint16 getCurrentPatientAge();
    bool getCurrentPatientSex();


    /*! Возвращает true, если в БД врача отсутствуют профили */
    bool getIsDoctorDbExists();

signals:
    void setPatientProfile(QString insuranceNumber);
    void changeDoctorProfile();

public slots:
    void addNewPatient(QString fullName, quint16 age, bool sex,
                       QString birthDate, QString address,
                       quint16 phoneNumber, QString occupation);

    void addNewDoctorProfile(QString doctorFullName, QString doctorSpecialization,
                             QString doctorInstitutionName, quint16 doctorInstitutionCode,
                             QString doctorInstitutionAddress, quint16 doctorInn,
                             QString doctorLicenseInfo);

    void setCurrentDoctorInn(quint16 inn);

    void setPatient(QString fullName);
};

#endif // BACKEND_H
