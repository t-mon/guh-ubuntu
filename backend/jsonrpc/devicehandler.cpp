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
            Vendor vendor = JsonTypes::unpackVendor(vendorVariant.toMap());
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
            DeviceClass deviceClass = JsonTypes::unpackDeviceClass(deviceClassVariant.toMap());
            Core::instance()->deviceManager()->deviceClasses()->addDeviceClass(deviceClass);
        }
    }
}
