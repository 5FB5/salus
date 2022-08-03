#ifndef PATIENTCARDRECORD_H
#define PATIENTCARDRECORD_H

#include <QString>
#include <QList>

struct Record
{
    Record() {}

    QString data; // дата записи
    QString currentDiagnosis; // диагноз
    QString anamnesis; // анамнез
    QString treatment; // лечение

    QList<QString> complaints; // жалобы
    QList<QString> diseases; // перенесённые заболевания
};

#endif // PATIENTCARDRECORD_H
