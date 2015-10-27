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

#include "deviceclassesfiltermodel.h"

#include <QDebug>

DeviceClassesFilterModel::DeviceClassesFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

QUuid DeviceClassesFilterModel::vendorId() const
{
    return m_vendorId;
}

void DeviceClassesFilterModel::setVendorId(const QUuid &vendorId)
{
    m_vendorId = vendorId;
    emit vendorIdChanged();

    qDebug() << "DeviceClassesFilter: set vendorId to" << vendorId;

    invalidateFilter();
    sortRole();
}

DeviceClasses *DeviceClassesFilterModel::deviceClasses()
{
    return m_deviceClasses;
}

void DeviceClassesFilterModel::setDeviceClasses(DeviceClasses *deviceClasses)
{
    m_deviceClasses = deviceClasses;
    setSourceModel(deviceClasses);
    emit deviceClassesChanged();
}


void DeviceClassesFilterModel::resetFilter()
{
    qDebug() << "DeviceClassesFilter: reset filter";
    setVendorId(QUuid());
    invalidateFilter();
}

bool DeviceClassesFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
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
