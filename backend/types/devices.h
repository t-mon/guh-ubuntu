#ifndef DEVICES_H
#define DEVICES_H

#include <QAbstractListModel>

#include "device.h"

class Devices : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DeviceRole {
        NameRole,
        IdRole,
        DeviceClassRole,
        SetupComplete
    };

    explicit Devices(QObject *parent = 0);

    QList<Device *> devices();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addDevice(Device *device);
    void removeDevice(Device *device);

    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Device *> m_devices;

    int indexOf(Device *device);
};

#endif // DEVICES_H
