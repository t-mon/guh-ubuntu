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

#include "jsontypes.h"

JsonTypes::JsonTypes(QObject *parent) :
    QObject(parent)
{
}

Vendor JsonTypes::unpackVendor(const QVariantMap &vendorMap)
{
    QString name = vendorMap.value("name").toString();
    QUuid id = vendorMap.value("id").toUuid();
    return Vendor(id, name);
}

DeviceClass JsonTypes::unpackDeviceClass(const QVariantMap &deviceClassMap)
{
    DeviceClass deviceClass;
    deviceClass.setName(deviceClassMap.value("name").toString());
    deviceClass.setId(deviceClassMap.value("id").toUuid());
    deviceClass.setVendorId(deviceClassMap.value("vendorId").toUuid());
    return deviceClass;
}
