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

#include "../types/vendors.h"
#include "../types/deviceclasses.h"
#include "../types/params.h"
#include "../types/paramtypes.h"

#include <QMetaEnum>

JsonTypes::JsonTypes(QObject *parent) :
    QObject(parent)
{
}

Vendor *JsonTypes::unpackVendor(const QVariantMap &vendorMap, QObject *parent)
{
    return new Vendor(vendorMap.value("id").toUuid(), vendorMap.value("name").toString(), parent);
}

DeviceClass *JsonTypes::unpackDeviceClass(const QVariantMap &deviceClassMap, QObject *parent)
{
    DeviceClass *deviceClass = new DeviceClass(parent);
    deviceClass->setName(deviceClassMap.value("name").toString());
    deviceClass->setId(deviceClassMap.value("id").toUuid());
    deviceClass->setVendorId(deviceClassMap.value("vendorId").toUuid());
    QVariantList createMethodsList = deviceClassMap.value("createMethods").toList();
    QStringList createMethods;
    foreach (QVariant method, createMethodsList) {
        createMethods.append(method.toString());
    }
    deviceClass->setCreateMethods(createMethods);
    deviceClass->setSetupMethod(stringToSetupMethod(deviceClassMap.value("setupMethod").toString()));

    // ParamTypes
    ParamTypes *paramTypes = new ParamTypes(deviceClass);
    foreach (QVariant paramType, deviceClassMap.value("paramTypes").toList()) {
        paramTypes->addParamType(JsonTypes::unpackParamType(paramType.toMap(), paramTypes));
    }
    deviceClass->setParamTypes(paramTypes);

    // discovery ParamTypes
    ParamTypes *discoveryParamTypes = new ParamTypes(deviceClass);
    foreach (QVariant paramType, deviceClassMap.value("discoveryParamTypes").toList()) {
        discoveryParamTypes->addParamType(JsonTypes::unpackParamType(paramType.toMap(), discoveryParamTypes));
    }
    deviceClass->setDiscoveryParamTypes(discoveryParamTypes);


    // StateTypes
    StateTypes *stateTypes = new StateTypes(deviceClass);
    foreach (QVariant stateType, deviceClassMap.value("stateTypes").toList()) {
        stateTypes->addStateType(JsonTypes::unpackStateType(stateType.toMap(), stateTypes));
    }
    deviceClass->setStateTypes(stateTypes);

    // EventTypes
    EventTypes *eventTypes = new EventTypes(deviceClass);
    foreach (QVariant eventType, deviceClassMap.value("eventTypes").toList()) {
        eventTypes->addEventType(JsonTypes::unpackEventType(eventType.toMap(), eventTypes));
    }
    deviceClass->setEventTypes(eventTypes);

    // ActionTypes
    ActionTypes *actionTypes = new ActionTypes(deviceClass);
    foreach (QVariant actionType, deviceClassMap.value("actionTypes").toList()) {
        actionTypes->addActionType(JsonTypes::unpackActionType(actionType.toMap(), actionTypes));
    }
    deviceClass->setActionTypes(actionTypes);

    return deviceClass;
}

Param *JsonTypes::unpackParam(const QVariantMap &paramMap, QObject *parent)
{
    return new Param(paramMap.value("name").toString(), paramMap.value("value"), parent);
}

ParamType *JsonTypes::unpackParamType(const QVariantMap &paramTypeMap, QObject *parent)
{
    ParamType *paramType = new ParamType(parent);
    paramType->setName(paramTypeMap.value("name").toString());
    paramType->setType(paramTypeMap.value("type").toString());
    paramType->setDefaultValue(paramTypeMap.value("defaultValue"));
    paramType->setMinValue(paramTypeMap.value("minValue"));
    paramType->setMaxValue(paramTypeMap.value("maxValue"));
    paramType->setAllowedValues(paramTypeMap.value("allowedValues").toList());
    paramType->setInputType(stringToInputType(paramTypeMap.value("inputType").toString()));
    paramType->setReadOnly(paramTypeMap.value("readOnly").toBool());
    QPair<Types::Unit, QString> unit = stringToUnit(paramTypeMap.value("unit").toString());
    paramType->setUnit(unit.first);
    paramType->setUnitString(unit.second);
    return paramType;
}

StateType *JsonTypes::unpackStateType(const QVariantMap &stateTypeMap, QObject *parent)
{
    StateType *stateType = new StateType(parent);
    stateType->setId(stateTypeMap.value("id").toUuid());
    stateType->setName(stateTypeMap.value("name").toString());
    stateType->setDefaultValue(stateTypeMap.value("defaultValue"));
    stateType->setType(stateTypeMap.value("type").toString());
    QPair<Types::Unit, QString> unit = stringToUnit(stateTypeMap.value("unit").toString());
    stateType->setUnit(unit.first);
    stateType->setUnitString(unit.second);
    return stateType;
}

EventType *JsonTypes::unpackEventType(const QVariantMap &eventTypeMap, QObject *parent)
{
    EventType *eventType = new EventType(parent);
    eventType->setId(eventTypeMap.value("id").toUuid());
    eventType->setName(eventTypeMap.value("name").toString());
    ParamTypes *paramTypes = new ParamTypes(eventType);
    foreach (QVariant paramType, eventTypeMap.value("paramTypes").toList()) {
        paramTypes->addParamType(JsonTypes::unpackParamType(paramType.toMap(), paramTypes));
    }
    eventType->setParamTypes(paramTypes);
    return eventType;
}

ActionType *JsonTypes::unpackActionType(const QVariantMap &actionTypeMap, QObject *parent)
{
    ActionType *actionType = new ActionType(parent);
    actionType->setId(actionTypeMap.value("id").toUuid());
    actionType->setName(actionTypeMap.value("name").toString());
    ParamTypes *paramTypes = new ParamTypes(actionType);
    foreach (QVariant paramType, actionTypeMap.value("paramTypes").toList()) {
        paramTypes->addParamType(JsonTypes::unpackParamType(paramType.toMap(), paramTypes));
    }
    actionType->setParamTypes(paramTypes);
    return actionType;
}

Device *JsonTypes::unpackDevice(const QVariantMap &deviceMap, QObject *parent)
{
    Device *device = new Device(parent);
    device->setDeviceName(deviceMap.value("name").toString());
    device->setId(deviceMap.value("id").toUuid());
    device->setDeviceClassId(deviceMap.value("deviceClassId").toUuid());
    device->setSetupComplete(deviceMap.value("setupComplete").toBool());

    Params *params = new Params(device);
    foreach (QVariant param, deviceMap.value("params").toList()) {
        params->addParam(JsonTypes::unpackParam(param.toMap(), params));
    }
    device->setParams(params);
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
