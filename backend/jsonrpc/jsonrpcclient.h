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

#ifndef JSONRPCCLIENT_H
#define JSONRPCCLIENT_H

#include <QObject>
#include <QVariantMap>

#include "devicehandler.h"

class JsonRpcReply;
class JsonHandler;
class Param;
class Params;

class JsonRpcClient : public QObject
{
    Q_OBJECT
public:
    explicit JsonRpcClient(QObject *parent = 0);

    // internal
    void getVendors();
    void getDevices();
    void getDeviceClasses();

    // ui methods
    Q_INVOKABLE int addDevice(const QUuid &deviceClassId, const QVariantList &deviceParams);
    Q_INVOKABLE int addDiscoveredDevice(const QUuid &deviceClassId, const QUuid &deviceDescriptorId);
    Q_INVOKABLE int removeDevice(const QUuid &deviceId);
    Q_INVOKABLE int discoverDevices(const QUuid &deviceClassId, const QVariantList &discoveryParams = QVariantList());

private:
    int m_id;
    QHash<QString, JsonHandler *> m_handlers;
    QHash<int, JsonRpcReply *> m_replies;

    DeviceHandler *m_deviceHandler;

    JsonRpcReply *createReply(QString nameSpace, QString method, QVariantMap params = QVariantMap());

signals:
    void responseReceived(const int &commandId, const QVariantMap &response);

public slots:
    void dataReceived(const QVariantMap &data);

};


class JsonRpcReply : public QObject
{
    Q_OBJECT
public:
    explicit JsonRpcReply(int commandId, QString nameSpace, QString method, QVariantMap params = QVariantMap(), QObject *parent = 0);

    int commandId() const;
    QString nameSpace() const;
    QString method() const;
    QVariantMap params() const;
    QVariantMap requestMap();

private:
    int m_commandId;
    QString m_nameSpace;
    QString m_method;
    QVariantMap m_params;
};


#endif // JSONRPCCLIENT_H
