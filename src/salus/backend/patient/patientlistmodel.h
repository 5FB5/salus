#ifndef PATIENTLISTMODEL_H
#define PATIENTLISTMODEL_H

#include <QAbstractListModel>

#include "patientdatabase.h"

class PatientListModel : public QAbstractListModel
{
    Q_OBJECT

private:
    QList<Patient> mPatientsList;

public:
    explicit PatientListModel(QObject *parent = nullptr);

    enum {
        role_patient_name
    };

    PatientDataBase patientDb;

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    void reloadPatientList();

signals:
    void modelReloaded();

};

#endif // PATIENTLISTMODEL_H
