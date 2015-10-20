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

#include "devicehandler.h"
#include "../core.h"
#include "jsontypes.h"

DeviceHandler::DeviceHandler(QObject *parent) :
    JsonHandler(parent)
{
}

QString DeviceHandler::nameSpace() const
{
    return QString("Devices");
}

void DeviceHandler::processGetSupportedVendors(const QVariantMap &params)
{
    if (params.value("params").toMap().keys().contains("vendors")) {
        QVariantList vendorList = params.value("params").toMap().value("vendors").toList();
        foreach (QVariant vendorVariant, vendorList) {
            Vendor *vendor = JsonTypes::unpackVendor(vendorVariant.toMap(), Core::instance()->deviceManager()->vendors());
            Core::instance()->deviceManager()->vendors()->addVendor(vendor);
        }
    }
    Core::instance()->jsonRpcClient()->getDeviceClasses();
}

void DeviceHandler::processGetSupportedDevices(const QVariantMap &params)
{
    if (params.value("params").toMap().keys().contains("deviceClasses")) {
        QVariantList deviceClassList = params.value("params").toMap().value("deviceClasses").toList();
        foreach (QVariant deviceClassVariant, deviceClassList) {
            DeviceClass *deviceClass = JsonTypes::unpackDeviceClass(deviceClassVariant.toMap(), Core::instance()->deviceManager()->deviceClasses());
            Core::instance()->deviceManager()->deviceClasses()->addDeviceClass(deviceClass);
        }
    }
    Core::instance()->jsonRpcClient()->getDevices();
}

void DeviceHandler::processGetConfiguredDevices(const QVariantMap &params)
{
    if (params.value("params").toMap().keys().contains("devices")) {
        QVariantList deviceList = params.value("params").toMap().value("devices").toList();
        foreach (QVariant deviceVariant, deviceList) {
            Device *device = JsonTypes::unpackDevice(deviceVariant.toMap(), Core::instance()->deviceManager()->devices());
            Core::instance()->deviceManager()->devices()->addDevice(device);
        }
    }
}

void DeviceHandler::processRemoveConfiguredDevice(const QVariantMap &params)
{
    qDebug() << params;
}

void DeviceHandler::processAddConfiguredDevice(const QVariantMap &params)
{
    qDebug() << params;
}

void DeviceHandler::processDeviceRemoved(const QVariantMap &params)
{
    QUuid deviceId = params.value("params").toMap().value("deviceId").toUuid();
    qDebug() << "JsonRpc: Notification: Device removed" << deviceId.toString();
    Device *device = Core::instance()->deviceManager()->devices()->getDevice(deviceId);
    Core::instance()->deviceManager()->devices()->removeDevice(device);
    device->deleteLater();
}

void DeviceHandler::processDeviceAdded(const QVariantMap &params)
{
    if (params.value("params").toMap().keys().contains("device")) {
        QVariantMap deviceVariant = params.value("params").toMap().value("device").toMap();
        Device *device = JsonTypes::unpackDevice(deviceVariant, Core::instance()->deviceManager()->devices());
        qDebug() << "JsonRpc: Notification: Device added" << device->id().toString();
        Core::instance()->deviceManager()->devices()->addDevice(device);
    }

}
