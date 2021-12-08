#include "patientlistmodel.h"

PatientListModel::PatientListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    // Берём лист имён пациентов
    foreach(Patient p, *patientDb.patientsList) {
        patientNames.append(p.fullName);
    }
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

    // FIXME: Implement me!
    return patientNames.size();
}

QVariant PatientListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role) {
    case patientNameRole:
        foreach(QVariant patientName, patientNames) {
            return patientNames[index.row()];
        }
    }

    return QVariant();
}

bool PatientListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool PatientListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}

QHash<int, QByteArray> PatientListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[patientNameRole] = "patientName";
    return names;
}
