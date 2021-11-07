#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QFile>
#include <QFileInfo>
enum class SEX{
    MAN,WOMAN

};
class Patient
{
public:
    Patient();
    QString fullName;
    quint8 age;
    bool sex;
    QDate birthDate;
    QString adress;
    QString insuranceCompany;
    QString insuranceNumber;
    QString phoneNumber;
    QString occupation;
    QString diagnosis;
    QList<QString> diseases;
    QString diseaseDescription;


};

#endif // PATIENT_H
