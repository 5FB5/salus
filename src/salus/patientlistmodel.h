#ifndef PATIENTLISTMODEL_H
#define PATIENTLISTMODEL_H

#include <QAbstractListModel>

#include "patientdatabase.h"

class PatientListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PatientListModel(QObject *parent = nullptr);

    enum {
        patientNameRole = Qt::DisplayRole
    };

    PatientDataBase patientDb;

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual QHash<int, QByteArray> roleNames() const override;

private:
    QList<QString> patientNames;
};

#endif // PATIENTLISTMODEL_H
