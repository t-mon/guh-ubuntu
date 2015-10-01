#include "deviceclasses.h"

#include <QDebug>

DeviceClasses::DeviceClasses(QObject *parent) :
    QAbstractListModel(parent)
{

}

QList<DeviceClass> DeviceClasses::deviceClasses()
{
    return m_deviceClasses;
}

int DeviceClasses::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_deviceClasses.count();
}

QVariant DeviceClasses::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_deviceClasses.count())
        return QVariant();

    DeviceClass deviceClass = m_deviceClasses.at(index.row());
    if (role == NameRole) {
        return deviceClass.name();
    } else if (role == IdRole) {
        return deviceClass.id().toString();
    } else if (role == PluginIdRole) {
        return deviceClass.pluginId().toString();
    } else if (role == VendorIdRole) {
        return deviceClass.vendorId().toString();
    }
    return QVariant();
}

DeviceClass DeviceClasses::get(int index)
{
    if (index > -1 && index < m_deviceClasses.count()) {
        return m_deviceClasses.at(index);
    }
    return DeviceClass();
}

void DeviceClasses::addDeviceClass(DeviceClass deviceClass)
{
    beginInsertRows(QModelIndex(), m_deviceClasses.count(), m_deviceClasses.count());
    qDebug() << "DeviceClasses: loaded deviceClass" << deviceClass.name();
    m_deviceClasses.append(deviceClass);
    endInsertRows();
}

void DeviceClasses::clearModel()
{
    beginResetModel();
    m_deviceClasses.clear();
    endResetModel();
}

QHash<int, QByteArray> DeviceClasses::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IdRole] = "id";
    roles[PluginIdRole] = "pluginId";
    roles[VendorIdRole] = "vendorId";
    return roles;
}
