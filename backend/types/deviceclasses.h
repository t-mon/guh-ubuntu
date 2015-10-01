#ifndef DEVICECLASSMODEL_H
#define DEVICECLASSMODEL_H

#include <QAbstractListModel>

#include "deviceclass.h"

class DeviceClasses : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DeviceClassRole {
        NameRole,
        IdRole,
        PluginIdRole,
        VendorIdRole
    };

    explicit DeviceClasses(QObject *parent = 0);

    QList<DeviceClass> deviceClasses();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE DeviceClass get(int index);

    void addDeviceClass(DeviceClass deviceClass);

    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<DeviceClass> m_deviceClasses;

};

#endif // DEVICECLASSMODEL_H
