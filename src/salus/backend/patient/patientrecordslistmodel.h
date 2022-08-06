#ifndef PATIENTRECORDSLISTMODEL_H
#define PATIENTRECORDSLISTMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "patientdatabase.h"

class PatientRecordsListModel : public QAbstractListModel
{
public:
    enum {
        role_record_name
    };

    PatientRecordsListModel();

    QList<Record_t> recordsList;

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;
};

#endif // PATIENTRECORDSLISTMODEL_H
