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

#include "core.h"

Core* Core::s_instance = 0;

Core *Core::instance()
{
    if (!s_instance)
        s_instance = new Core();

    return s_instance;
}

QObject *Core::qmlInstance(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    Q_UNUSED(qmlEngine)
    Q_UNUSED(jsEngine)
    return Core::instance();
}

Core::Core(QObject *parent) :
    QObject(parent),
    m_deviceManager(new DeviceManager(this)),
    m_interface(new GuhInterface(this)),
    m_jsonRpcClient(new JsonRpcClient(this)),
    m_discovery(new UpnpDiscovery(this))
{
    connect(m_interface, &GuhInterface::connectedChanged, this, &Core::connectedChanged);
    connect(m_interface, &GuhInterface::dataReady, m_jsonRpcClient, &JsonRpcClient::dataReceived);
}

DeviceManager *Core::deviceManager()
{
    return m_deviceManager;
}

UpnpDiscovery *Core::discovery()
{
    return m_discovery;
}

GuhInterface *Core::interface()
{
    return m_interface;
}

JsonRpcClient *Core::jsonRpcClient()
{
    return m_jsonRpcClient;
}

bool Core::connected() const
{
    return m_interface->connected();
}

