#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QFile>
#include <QFileInfo>
//#include <QDate>

enum class SexType {
    MAN,
    WOMAN
};

class Patient
{

public:
    Patient();
    //      ФИО         Адрес      Профессия   Текущий диагноз, Анамнез
    QString fullName, address, occupation, currentDiagnosis, anamnesis;
    QString birthDate; // TODO: это должно быть QDate, но непонятно где это использовать

    QList<QString> complaints; // жалобы
    QList<QString> diseases; // перенесённые заболевания

    bool sex;

    //          Моб. телефон
    quint16 age, phoneNumber;

};

#endif // PATIENT_H
