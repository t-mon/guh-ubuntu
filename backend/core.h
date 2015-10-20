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

#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

#include "guhinterface.h"
#include "jsonrpc/jsonrpcclient.h"
#include "devicemanager.h"
#include "discovery/upnpdiscovery.h"

class Core : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GuhInterface *interface READ interface CONSTANT)
    Q_PROPERTY(UpnpDiscovery *discovery READ discovery CONSTANT)
    Q_PROPERTY(DeviceManager *deviceManager READ deviceManager CONSTANT)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)

public:
    static Core* instance();
    static QObject *qmlInstance(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    DeviceManager *deviceManager();
    GuhInterface *interface();
    JsonRpcClient *jsonRpcClient();
    UpnpDiscovery *discovery();

    bool connected() const;

private:
    explicit Core(QObject *parent = 0);
    static Core *s_instance;

    DeviceManager *m_deviceManager;
    GuhInterface *m_interface;
    JsonRpcClient *m_jsonRpcClient;
    UpnpDiscovery *m_discovery;

    bool m_connected;

signals:
    void connectedChanged();

private slots:
    void onConnectionChanged();

};

#endif // CORE_H
