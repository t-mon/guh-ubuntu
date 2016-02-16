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

#include "actiontype.h"

ActionType::ActionType(QObject *parent) :
    QObject(parent)
{
}

QUuid ActionType::id() const
{
    return m_id;
}

void ActionType::setId(const QUuid &id)
{
    m_id = id;
}

QString ActionType::name() const
{
    return m_name;
}

void ActionType::setName(const QString &name)
{
    m_name = name;
}

ParamTypes *ActionType::paramTypes() const
{
    return m_paramTypes;
}

void ActionType::setParamTypes(ParamTypes *paramTypes)
{
    m_paramTypes = paramTypes;
    emit paramTypesChanged();
}

