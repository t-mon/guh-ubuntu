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

#include "statetype.h"

StateType::StateType(QObject *parent) :
    QObject(parent)
{
}

QUuid StateType::id() const
{
    return m_id;
}

void StateType::setId(const QUuid &id)
{
    m_id = id;
}

QString StateType::name() const
{
    return m_name;
}

void StateType::setName(const QString &name)
{
    m_name = name;
}

QString StateType::type() const
{
    return m_type;
}

void StateType::setType(const QString &type)
{
    m_type = type;
}

QVariant StateType::defaultValue() const
{
    return m_defaultValue;
}

void StateType::setDefaultValue(const QVariant &defaultValue)
{
    m_defaultValue = defaultValue;
}

Types::Unit StateType::unit() const
{
    return m_unit;
}

void StateType::setUnit(const Types::Unit &unit)
{
    m_unit = unit;
}

QString StateType::unitString() const
{
    return m_unitString;
}

void StateType::setUnitString(const QString &unitString)
{
    m_unitString = unitString;
}

