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
    QString treatmentResult; // результаты лечения
    QString diseases; // перенесённые заболевания FIXME: временно используется для хранения данных исследования
};

#endif // PATIENTCARDRECORD_H
