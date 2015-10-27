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

#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>

#include "types/vendors.h"
#include "types/devices.h"
#include "types/devicesproxy.h"
#include "types/deviceclasses.h"
#include "types/deviceclassesproxy.h"

class DeviceManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Vendors *vendors READ vendors CONSTANT)
    Q_PROPERTY(Devices *devices READ devices CONSTANT)
    Q_PROPERTY(DevicesProxy *devicesProxy READ devicesProxy CONSTANT)
    Q_PROPERTY(DeviceClasses *deviceClasses READ deviceClasses CONSTANT)
    Q_PROPERTY(DeviceClassesProxy *deviceClassesProxy READ deviceClassesProxy CONSTANT)

public:
    explicit DeviceManager(QObject *parent = 0);

    Vendors *vendors() const;
    Devices *devices() const;
    DevicesProxy *devicesProxy() const;
    DeviceClasses *deviceClasses() const;
    DeviceClassesProxy *deviceClassesProxy() const;

private:
    Vendors *m_vendors;
    Devices *m_devices;
    DevicesProxy *m_devicesProxy;
    DeviceClasses *m_deviceClasses;
    DeviceClassesProxy *m_deviceClassesProxy;

};

#endif // DEVICEMANAGER_H
