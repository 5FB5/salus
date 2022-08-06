#include "patientrecordslistmodel.h"

PatientRecordsListModel::PatientRecordsListModel()
{

}

QVariant PatientRecordsListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int PatientRecordsListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return recordsList.size();
}

QVariant PatientRecordsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || recordsList.isEmpty())
        return QVariant();

    const Record_t currentRecord = recordsList.at(index.row());
    return QVariant(currentRecord.date);
}

QHash<int, QByteArray> PatientRecordsListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[role_record_name] = "role_record_name";
    return names;
}
