/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2015 Simon Stuerz <stuerz.simon@gmail.com>               *
 *                                                                         *
 *  This file is part of guh-ubuntu.                                       *
 *                                                                         *
 *  guh-ubuntu is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 3 of the License.                *
 *                                                                         *
 *  guh-ubuntu is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with guh-ubuntu. If not, see <http://www.gnu.org/licenses/>.     *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "deviceclasses.h"

#include <QDebug>

DeviceClasses::DeviceClasses(QObject *parent) :
    QAbstractListModel(parent)
{

}

QList<DeviceClass *> DeviceClasses::deviceClasses()
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

    DeviceClass *deviceClass = m_deviceClasses.at(index.row());
    if (role == NameRole) {
        return deviceClass->name();
    } else if (role == IdRole) {
        return deviceClass->id().toString();
    } else if (role == PluginIdRole) {
        return deviceClass->pluginId().toString();
    } else if (role == VendorIdRole) {
        return deviceClass->vendorId().toString();
    }
    return QVariant();
}

DeviceClass *DeviceClasses::get(int index) const
{
    return m_deviceClasses.at(index);
}

DeviceClass *DeviceClasses::getDeviceClass(QUuid deviceClassId) const
{
    foreach (DeviceClass *deviceClass, m_deviceClasses) {
        if (deviceClass->id() == deviceClassId) {
            return deviceClass;
        }
    }
    return 0;
}

void DeviceClasses::addDeviceClass(DeviceClass *deviceClass)
{
    beginInsertRows(QModelIndex(), m_deviceClasses.count(), m_deviceClasses.count());
    qDebug() << "DeviceClasses: loaded deviceClass" << deviceClass->name();
    m_deviceClasses.append(deviceClass);
    endInsertRows();
}

void DeviceClasses::clearModel()
{
    beginResetModel();
    qDebug() << "Devices: delete all deviceClasses";
    qDeleteAll(m_deviceClasses);
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
