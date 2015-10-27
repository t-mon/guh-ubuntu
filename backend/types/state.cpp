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

#include "state.h"

State::State(const QUuid &deviceId, const QUuid &stateTypeId, const QVariant &value, QObject *parent) :
    QObject(parent),
    m_deviceId(deviceId),
    m_stateTypeId(stateTypeId),
    m_value(value)
{
}

QUuid State::deviceId() const
{
    return m_deviceId;
}

QUuid State::stateTypeId() const
{
    return m_stateTypeId;
}

QVariant State::value() const
{
    return m_value;
}

void State::setValue(const QVariant &value)
{
    m_value = value;
    emit valueChanged();
}

