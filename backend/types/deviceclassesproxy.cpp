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

#include "deviceclassesproxy.h"

#include <QDebug>

DeviceClassesProxy::DeviceClassesProxy(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

QUuid DeviceClassesProxy::vendorId() const
{
    return m_vendorId;
}

void DeviceClassesProxy::setVendorId(const QUuid &vendorId)
{
    m_vendorId = vendorId;
    emit vendorIdChanged();

    qDebug() << "DeviceClassesProxy: set vendorId filter" << vendorId;

    invalidateFilter();
    sort(0);
}

DeviceClasses *DeviceClassesProxy::deviceClasses()
{
    return m_deviceClasses;
}

void DeviceClassesProxy::setDeviceClasses(DeviceClasses *deviceClasses)
{
    m_deviceClasses = deviceClasses;
    setSourceModel(deviceClasses);
    emit deviceClassesChanged();
}


void DeviceClassesProxy::resetFilter()
{
    qDebug() << "DeviceClassesProxy: reset filter";
    setVendorId(QUuid());
    invalidateFilter();
}

bool DeviceClassesProxy::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    Q_UNUSED(sourceParent)

    DeviceClass *deviceClass = m_deviceClasses->get(sourceRow);

    // filter auto devices
    if (deviceClass->createMethods().count() == 1 && deviceClass->createMethods().contains("CreateMethodAuto"))
        return false;

    if (!m_vendorId.isNull() && deviceClass->vendorId() == m_vendorId)
        return true;

    return false;
}

bool DeviceClassesProxy::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftName = sourceModel()->data(left);
    QVariant rightName = sourceModel()->data(right);

    return QString::localeAwareCompare(leftName.toString(), rightName.toString()) < 0;
}
