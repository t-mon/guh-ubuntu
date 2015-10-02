#include "devices.h"

#include <QDebug>

Devices::Devices(QObject *parent) :
    QAbstractListModel(parent)
{
}

QList<Device *> Devices::devices()
{
    return m_devices;
}

int Devices::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_devices.count();
}

QVariant Devices::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_devices.count())
        return QVariant();

    Device *device = m_devices.at(index.row());
    if (role == NameRole) {
        return device->name();
    } else if (role == IdRole) {
        return device->id().toString();
    } else if (role == DeviceClassRole) {
        return device->deviceClassId().toString();
    } else if (role == SetupComplete) {
        return device->setupComplete();
    }
    return QVariant();

}

void Devices::addDevice(Device *device)
{
    beginInsertRows(QModelIndex(), m_devices.count(), m_devices.count());
    qDebug() << "Devices: loaded device" << device->name();
    m_devices.append(device);
    endInsertRows();
}

void Devices::removeDevice(Device *device)
{
    beginRemoveRows(QModelIndex(), m_devices.indexOf(device), m_devices.indexOf(device));
    qDebug() << "Devices: removed device" << device->name();
    m_devices.removeAll(device);
    endInsertRows();
}

void Devices::clearModel()
{
    beginResetModel();
    m_devices.clear();
    endResetModel();
}

QHash<int, QByteArray> Devices::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IdRole] = "id";
    roles[DeviceClassRole] = "deviceClassId";
    roles[SetupComplete] = "setupComplete";
    return roles;
}

int Devices::indexOf(Device *device)
{
    return m_devices.indexOf(device);
}
