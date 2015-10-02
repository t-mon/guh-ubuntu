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

#include "devicemanager.h"



DeviceManager::DeviceManager(QObject *parent) :
    QObject(parent),
    m_vendors(new Vendors(this)),
    m_devices(new Devices(this)),
    m_deviceClasses(new DeviceClasses(this)),
    m_deviceClassesFilter(new DeviceClassesFilterModel(this))

{
    m_deviceClassesFilter->setDeviceClasses(m_deviceClasses);
}

Vendors *DeviceManager::vendors()
{
    return m_vendors;
}

Devices *DeviceManager::devices()
{
    return m_devices;
}

DeviceClasses *DeviceManager::deviceClasses()
{
    return m_deviceClasses;
}

DeviceClassesFilterModel *DeviceManager::deviceClassesFilter()
{
    return m_deviceClassesFilter;
}
