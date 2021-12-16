#include "patientlistmodel.h"

PatientListModel::PatientListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    reloadPatientList();
}

QVariant PatientListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int PatientListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return mPatientsList.size();
}

QVariant PatientListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || mPatientsList.isEmpty())
        return QVariant();

    const Patient currentPatient = mPatientsList.at(index.row());

    return QVariant(currentPatient.fullName);
}

void PatientListModel::reloadPatientList()
{
    qDebug() << "Salus: [PatientListModel::reloadPatientList()] - Reloading patient list...\n";
    beginResetModel();
    mPatientsList.clear();

    // взять заного данные из файла
    patientDb.getPatientsListFromJson();

    foreach(Patient p, *patientDb.patientsList) {
        mPatientsList.append(p);
    }

    endResetModel();

    qDebug() << "Salus: [PatientListModel::reloadPatientList()] - Patient list reloaded!\n";

    qDebug() << "Salus: [PatientListModel::reloadPatientList()] - Current patient list is: ";
    foreach(Patient p, mPatientsList) {
        qDebug() << "\t" << p.fullName;
    }
}

QHash<int, QByteArray> PatientListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[role_patient_name] = "role_patient_name";
    return names;
}
