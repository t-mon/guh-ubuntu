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

#include "device.h"

Device::Device(QObject *parent) :
    QObject(parent)
{
}

QString Device::name() const
{
    return m_name;
}

void Device::setName(const QString &name)
{
    m_name = name;
    emit nameChanged();
}

QUuid Device::id() const
{
    return m_id;
}

void Device::setId(const QUuid &id)
{
    m_id = id;
}

QUuid Device::deviceClassId() const
{
    return m_deviceClassId;
}

void Device::setDeviceClassId(const QUuid &deviceClassId)
{
    m_deviceClassId = deviceClassId;
}

Params *Device::params() const
{
    return m_params;
}

void Device::setParams(Params *params)
{
    m_params = params;
    emit paramsChanged();
}

bool Device::setupComplete()
{
    return m_setupComplete;
}

void Device::setSetupComplete(const bool &setupComplete)
{
    m_setupComplete = setupComplete;
    emit setupCompleteChanged();
}
