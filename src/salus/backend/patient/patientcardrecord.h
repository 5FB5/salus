#ifndef PATIENTCARDRECORD_H
#define PATIENTCARDRECORD_H

#include <QString>
#include <QList>

struct Record_t
{
    QString date; // дата записи
    QString currentDiagnosis; // диагноз
    QString anamnesis; // анамнез
    QString treatment; // лечение

    QString complaints; // жалобы
    QString diseases; // перенесённые заболевания
};

#endif // PATIENTCARDRECORD_H
