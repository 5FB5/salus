#ifndef DOCTOR_H
#define DOCTOR_H

#include <QObject>

class Doctor : public QObject
{
    Q_OBJECT
public:
    explicit Doctor(QObject *parent = nullptr);

signals:

};

#endif // DOCTOR_H
