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

#include "deviceclass.h"

#include <QDebug>

DeviceClass::DeviceClass(QObject *parent) :
    QObject(parent)
{
}

QUuid DeviceClass::id() const
{
    return m_id;
}

void DeviceClass::setId(const QUuid &id)
{
    m_id = id;
}

QUuid DeviceClass::vendorId() const
{
    return m_vendorId;
}

void DeviceClass::setVendorId(const QUuid &vendorId)
{
    m_vendorId = vendorId;
}

QUuid DeviceClass::pluginId() const
{
    return m_pluginId;
}

void DeviceClass::setPluginId(const QUuid &pluginId)
{
    m_pluginId = pluginId;
}

QString DeviceClass::name() const
{
    return m_name;
}

void DeviceClass::setName(const QString &name)
{
    m_name = name;
}

QStringList DeviceClass::createMethods() const
{
    return m_createMethods;
}

void DeviceClass::setCreateMethods(const QStringList &createMethods)
{
    m_createMethods = createMethods;
}

DeviceClass::SetupMethod DeviceClass::setupMethod() const
{
    return m_setupMethod;
}

void DeviceClass::setSetupMethod(DeviceClass::SetupMethod setupMethod)
{
    m_setupMethod = setupMethod;
}

ParamTypes *DeviceClass::paramTypes() const
{
    return m_paramTypes;
}

void DeviceClass::setParamTypes(ParamTypes *paramTypes)
{
    m_paramTypes = paramTypes;
    emit paramTypesChanged();
}

ParamTypes *DeviceClass::discoveryParamTypes() const
{
    return m_discoveryParamTypes;
}

void DeviceClass::setDiscoveryParamTypes(ParamTypes *paramTypes)
{
    m_discoveryParamTypes = paramTypes;
    emit discoveryParamTypesChanged();
}

StateTypes *DeviceClass::stateTypes() const
{
    return m_stateTypes;
}

void DeviceClass::setStateTypes(StateTypes *stateTypes)
{
    m_stateTypes = stateTypes;
    emit stateTypesChanged();
}

EventTypes *DeviceClass::eventTypes() const
{
    return m_eventTypes;
}

void DeviceClass::setEventTypes(EventTypes *eventTypes)
{
    m_eventTypes = eventTypes;
    emit eventTypesChanged();
}

ActionTypes *DeviceClass::actionTypes() const
{
    return m_actionTypes;
}

void DeviceClass::setActionTypes(ActionTypes *actionTypes)
{
    m_actionTypes = actionTypes;
    emit actionTypesChanged();
}
