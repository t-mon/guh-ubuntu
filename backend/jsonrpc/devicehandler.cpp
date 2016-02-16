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
#include "jsontypes.h"
#include "../core.h"
#include "../types/states.h"
#include "../types/deviceclass.h"

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

void DeviceHandler::processGetPlugins(const QVariantMap &params)
{
    if (params.value("params").toMap().keys().contains("plugins")) {
        QVariantList pluginList = params.value("params").toMap().value("plugins").toList();
        foreach (QVariant pluginVariant, pluginList) {
            Plugin *plugin = JsonTypes::unpackPlugin(pluginVariant.toMap(), Core::instance()->deviceManager()->plugins());
            Core::instance()->deviceManager()->plugins()->addPlugin(plugin);
        }
    }
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

            // get state values
            Core::instance()->jsonRpcClient()->getStateValues(device->id());
        }
    }
}

void DeviceHandler::processGetStateValues(const QVariantMap &params)
{
    if (params.value("params").toMap().keys().contains("values")) {
        QVariantList stateVariantList = params.value("params").toMap().value("values").toList();

        foreach (const QVariant &stateMap, stateVariantList) {
            QUuid stateTypeId = stateMap.toMap().value("stateTypeId").toUuid();
            QVariant value = stateMap.toMap().value("value");

            // TODO: get device more performant
            foreach (Device *d, Core::instance()->deviceManager()->devices()->devices()) {
                if (d->hasState(stateTypeId)) {
                    d->setStateValue(stateTypeId, value);
                }
            }
        }
    }
}

void DeviceHandler::processRemoveConfiguredDevice(const QVariantMap &params)
{
    // response handled in the ui
    Q_UNUSED(params);
}

void DeviceHandler::processAddConfiguredDevice(const QVariantMap &params)
{
    // response handled in the ui
    Q_UNUSED(params);
}

void DeviceHandler::processGetDiscoveredDevices(const QVariantMap &params)
{
    // response handled in the ui
    Q_UNUSED(params);
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

void DeviceHandler::processStateChanged(const QVariantMap &params)
{
    QVariantMap notification = params.value("params").toMap();
    QUuid deviceId = notification.value("deviceId").toUuid();

    Device *device = Core::instance()->deviceManager()->devices()->getDevice(deviceId);

    if (!device) {
        qWarning() << "JsonRpc: ERROR: could not find device for state changed notification";
        return;
    }

    QUuid stateTypeId = notification.value("stateTypeId").toUuid();
    QVariant value = notification.value("value");

    device->setStateValue(stateTypeId, value);
}
