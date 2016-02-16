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

#include "plugin.h"

Plugin::Plugin(QObject *parent) : QObject(parent)
{

}

QString Plugin::name() const
{
    return m_name;
}

void Plugin::setName(const QString &name)
{
    m_name = name;
}

QUuid Plugin::pluginId() const
{
    return m_pluginId;
}

void Plugin::setPluginId(const QUuid pluginId)
{
    m_pluginId = pluginId;
}

ParamTypes *Plugin::paramTypes()
{
    return m_paramTypes;
}

void Plugin::setParamTypes(ParamTypes *paramTypes)
{
    m_paramTypes = paramTypes;
}

Params *Plugin::params()
{
    return m_params;
}

void Plugin::setParams(Params *params)
{
    m_params = params;
}

