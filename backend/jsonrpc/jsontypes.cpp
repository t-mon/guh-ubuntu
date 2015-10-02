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

#include "../types/vendor.h"
#include "../types/deviceclass.h"

#include "../core.h"

#include <QMetaEnum>

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
    QVariantList createMethodsList = deviceClassMap.value("createMethods").toList();
    QList<DeviceClass::CreateMethod> createMethods;
    foreach (QVariant createMethod, createMethodsList) {
        createMethods.append(JsonTypes::stringToCreateMethod(createMethod.toString()));
    }
    deviceClass.setCreateMethods(createMethods);
    deviceClass.setSetupMethod(stringToSetupMethod(deviceClassMap.value("setupMethod").toString()));

    // ParamTypes
    QList<ParamType> paramTypes;
    foreach (QVariant paramType, deviceClassMap.value("paramTypes").toList()) {
        paramTypes.append(JsonTypes::unpackParamType(paramType.toMap()));
    }
    deviceClass.setParamTypes(paramTypes);

    // discovery ParamTypes
    QList<ParamType> discoveryParamTypes;
    foreach (QVariant paramType, deviceClassMap.value("discoveryParamTypes").toList()) {
        discoveryParamTypes.append(JsonTypes::unpackParamType(paramType.toMap()));
    }
    deviceClass.setDiscoveryParamTypes(discoveryParamTypes);
    return deviceClass;
}

Param JsonTypes::unpackParam(const QVariantMap &paramMap)
{
    return Param(paramMap.value("name").toString(), paramMap.value("value"));
}

ParamType JsonTypes::unpackParamType(const QVariantMap &paramTypeMap)
{
    ParamType paramType;
    paramType.setName(paramTypeMap.value("name").toString());
    paramType.setType(QVariant::nameToType(paramTypeMap.value("type").toString().toLatin1().data()));
    paramType.setDefaultValue(paramTypeMap.value("defaultValue"));
    paramType.setMinValue(paramTypeMap.value("minValue"));
    paramType.setMaxValue(paramTypeMap.value("maxValue"));
    paramType.setAllowedValues(paramTypeMap.value("allowedValues").toList());
    paramType.setInputType(stringToInputType(paramTypeMap.value("inputType").toString()));
    paramType.setReadOnly(paramTypeMap.value("readOnly").toBool());
    QPair<Types::Unit, QString> unit = stringToUnit(paramTypeMap.value("unit").toString());
    paramType.setUnit(unit.first);
    paramType.setUnitString(unit.second);

    return paramType;
}

Device *JsonTypes::unpackDevice(const QVariantMap &deviceMap)
{
    Device *device = new Device(Core::instance()->deviceManager());
    device->setName(deviceMap.value("name").toString());
    device->setId(deviceMap.value("id").toUuid());
    device->setDeviceClassId(deviceMap.value("deviceClassId").toUuid());
    device->setSetupComplete(deviceMap.value("setupComplete").toBool());

    QList<Param> params;
    foreach (QVariant param, deviceMap.value("params").toList()) {
        params.append(JsonTypes::unpackParam(param.toMap()));
    }
    device->setSetupComplete(deviceMap.value("setupComplete").toBool());
    return device;
}

DeviceClass::SetupMethod JsonTypes::stringToSetupMethod(const QString &setupMethodString)
{
    if (setupMethodString == "SetupMethodJustAdd") {
        return DeviceClass::SetupMethodJustAdd;
    } else if (setupMethodString == "SetupMethodDisplayPin") {
        return DeviceClass::SetupMethodDisplayPin;
    } else if (setupMethodString == "SetupMethodEnterPin") {
        return DeviceClass::SetupMethodEnterPin;
    } else if (setupMethodString == "SetupMethodPushButton") {
        return DeviceClass::SetupMethodPushButton;
    }
    return DeviceClass::SetupMethodJustAdd;
}

DeviceClass::CreateMethod JsonTypes::stringToCreateMethod(const QString &createMethodString)
{
    if (createMethodString == "CreateMethodUser") {
        return DeviceClass::CreateMethodUser;
    } else if (createMethodString == "CreateMethodAuto") {
        return DeviceClass::CreateMethodAuto;
    } else if (createMethodString == "CreateMethodDiscovery") {
        return DeviceClass::CreateMethodDiscovery;
    }
    return DeviceClass::CreateMethodUser;
}

QPair<Types::Unit, QString> JsonTypes::stringToUnit(const QString &unitString)
{
    if (unitString == "UnitNone") {
        return QPair<Types::Unit, QString>(Types::UnitNone, "-");
    } else if (unitString == "UnitSeconds") {
        return QPair<Types::Unit, QString>(Types::UnitSeconds, "s");
    } else if (unitString == "UnitMinutes") {
        return QPair<Types::Unit, QString>(Types::UnitMinutes, "m");
    } else if (unitString == "UnitHours") {
        return QPair<Types::Unit, QString>(Types::UnitHours, "h");
    } else if (unitString == "UnitUnixTime") {
        return QPair<Types::Unit, QString>(Types::UnitUnixTime, "");
    } else if (unitString == "UnitMeterPerSecond") {
        return QPair<Types::Unit, QString>(Types::UnitMeterPerSecond, "m/s");
    } else if (unitString == "UnitKiloMeterPerHour") {
        return QPair<Types::Unit, QString>(Types::UnitKiloMeterPerHour, "km/h");
    } else if (unitString == "UnitDegree") {
        return QPair<Types::Unit, QString>(Types::UnitDegree, "°");
    } else if (unitString == "UnitRadiant") {
        return QPair<Types::Unit, QString>(Types::UnitRadiant, "rad");
    } else if (unitString == "UnitDegreeCelsius") {
        return QPair<Types::Unit, QString>(Types::UnitDegreeCelsius, "°C");
    } else if (unitString == "UnitDegreeKelvin") {
        return QPair<Types::Unit, QString>(Types::UnitDegreeKelvin, "°K");
    } else if (unitString == "UnitMired") {
        return QPair<Types::Unit, QString>(Types::UnitMired, "mir");
    } else if (unitString == "UnitMilliBar") {
        return QPair<Types::Unit, QString>(Types::UnitMilliBar, "mbar");
    } else if (unitString == "UnitBar") {
        return QPair<Types::Unit, QString>(Types::UnitBar, "bar");
    } else if (unitString == "UnitPascal") {
        return QPair<Types::Unit, QString>(Types::UnitPascal, "Pa");
    } else if (unitString == "UnitHectoPascal") {
        return QPair<Types::Unit, QString>(Types::UnitHectoPascal, "hPa");
    } else if (unitString == "UnitAtmosphere") {
        return QPair<Types::Unit, QString>(Types::UnitAtmosphere, "atm");
    } else if (unitString == "UnitLumen") {
        return QPair<Types::Unit, QString>(Types::UnitLumen, "lm");
    } else if (unitString == "UnitLux") {
        return QPair<Types::Unit, QString>(Types::UnitLux, "lx");
    } else if (unitString == "UnitCandela") {
        return QPair<Types::Unit, QString>(Types::UnitCandela, "cd");
    } else if (unitString == "UnitMilliMeter") {
        return QPair<Types::Unit, QString>(Types::UnitMilliMeter, "mm");
    } else if (unitString == "UnitCentiMeter") {
        return QPair<Types::Unit, QString>(Types::UnitCentiMeter, "cm");
    } else if (unitString == "UnitMeter") {
        return QPair<Types::Unit, QString>(Types::UnitMeter, "m");
    } else if (unitString == "UnitKiloMeter") {
        return QPair<Types::Unit, QString>(Types::UnitKiloMeter, "km");
    } else if (unitString == "UnitGram") {
        return QPair<Types::Unit, QString>(Types::UnitGram, "g");
    } else if (unitString == "UnitKiloGram") {
        return QPair<Types::Unit, QString>(Types::UnitKiloGram, "kg");
    } else if (unitString == "UnitDezibel") {
        return QPair<Types::Unit, QString>(Types::UnitDezibel, "db");
    } else if (unitString == "UnitKiloByte") {
        return QPair<Types::Unit, QString>(Types::UnitKiloByte, "kB");
    } else if (unitString == "UnitMegaByte") {
        return QPair<Types::Unit, QString>(Types::UnitMegaByte, "MB");
    } else if (unitString == "UnitGigaByte") {
        return QPair<Types::Unit, QString>(Types::UnitGigaByte, "GB");
    } else if (unitString == "UnitTeraByte") {
        return QPair<Types::Unit, QString>(Types::UnitTeraByte, "TB");
    } else if (unitString == "UnitMilliWatt") {
        return QPair<Types::Unit, QString>(Types::UnitMilliWatt, "mW");
    } else if (unitString == "UnitWatt") {
        return QPair<Types::Unit, QString>(Types::UnitWatt, "W");
    } else if (unitString == "UnitKiloWatt") {
        return QPair<Types::Unit, QString>(Types::UnitKiloWatt, "kW");
    } else if (unitString == "UnitKiloWattHour") {
        return QPair<Types::Unit, QString>(Types::UnitKiloWattHour, "kWh");
    } else if (unitString == "UnitPercentage") {
        return QPair<Types::Unit, QString>(Types::UnitPercentage, "%");
    } else if (unitString == "UnitEuro") {
        return QPair<Types::Unit, QString>(Types::UnitEuro, "€");
    } else if (unitString == "UnitDollar") {
        return QPair<Types::Unit, QString>(Types::UnitDollar, "$");
    }
    return QPair<Types::Unit, QString>(Types::UnitNone, "");
}

Types::InputType JsonTypes::stringToInputType(const QString &inputTypeString)
{
    if (inputTypeString == "InputTypeNone") {
        return Types::InputTypeNone;
    } else if (inputTypeString == "InputTypeTextLine") {
        return Types::InputTypeTextLine;
    } else if (inputTypeString == "InputTypeTextArea") {
        return Types::InputTypeTextArea;
    } else if (inputTypeString == "InputTypePassword") {
        return Types::InputTypePassword;
    } else if (inputTypeString == "InputTypeSearch") {
        return Types::InputTypeSearch;
    } else if (inputTypeString == "InputTypeMail") {
        return Types::InputTypeMail;
    } else if (inputTypeString == "InputTypeIPv4Address") {
        return Types::InputTypeIPv4Address;
    } else if (inputTypeString == "InputTypeIPv6Address") {
        return Types::InputTypeIPv6Address;
    } else if (inputTypeString == "InputTypeUrl") {
        return Types::InputTypeUrl;
    } else if (inputTypeString == "InputTypeMacAddress") {
        return Types::InputTypeMacAddress;
    }
    return Types::InputTypeNone;
}
