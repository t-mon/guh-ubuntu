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

#include "jsonrpcclient.h"
#include "../core.h"
#include "../types/param.h"
#include "../types/params.h"

#include <QJsonDocument>
#include <QVariantMap>
#include <QDebug>

JsonRpcClient::JsonRpcClient(QObject *parent) :
    QObject(parent),
    m_id(0)
{
    m_deviceHandler = new DeviceHandler(this);

    m_handlers.insert(m_deviceHandler->nameSpace(), m_deviceHandler);
}

void JsonRpcClient::getVendors()
{
    qDebug() << "JsonRpc: get vendors";
    JsonRpcReply *reply = createReply("Devices", "GetSupportedVendors");
    m_replies.insert(reply->commandId(), reply);
    Core::instance()->interface()->sendRequest(reply->requestMap());
}

void JsonRpcClient::getDevices()
{
    qDebug() << "JsonRpc: get devices";
    JsonRpcReply *reply = createReply("Devices", "GetConfiguredDevices");
    m_replies.insert(reply->commandId(), reply);
    Core::instance()->interface()->sendRequest(reply->requestMap());
}

void JsonRpcClient::getDeviceClasses()
{
    qDebug() << "JsonRpc: get supported devices";
    JsonRpcReply *reply = createReply("Devices", "GetSupportedDevices");
    m_replies.insert(reply->commandId(), reply);
    Core::instance()->interface()->sendRequest(reply->requestMap());
}

void JsonRpcClient::addDevice(const QUuid &deviceClassId, Params *params)
{
    qDebug() << "JsonRpc: add device " << deviceClassId.toString() << "with params";
    foreach (Param *param, params->params()) {
        qDebug() << "    -> " << param->name() << param->value();
    }

}

void JsonRpcClient::deleteDevice(const QUuid &deviceId)
{
    qDebug() << "JsonRpc: delete device" << deviceId.toString();
    QVariantMap params;
    params.insert("deviceId", deviceId.toString());
    JsonRpcReply *reply = createReply("Devices", "RemoveConfiguredDevice", params);
    m_replies.insert(reply->commandId(), reply);
    Core::instance()->interface()->sendRequest(reply->requestMap());
}

JsonRpcReply *JsonRpcClient::createReply(QString nameSpace, QString method, QVariantMap params)
{
    m_id++;
    return new JsonRpcReply(m_id, nameSpace, method, params, this);
}

void JsonRpcClient::dataReceived(const QVariantMap &data)
{
    int commandId = data.value("id").toInt();
    JsonRpcReply *reply = m_replies.take(commandId);

    // check if this is a reply to a request
    if (reply) {
        qDebug() << "JsonRpc: got response for" << QString("%1.%2").arg(reply->nameSpace(), reply->method());
        JsonHandler *handler = m_handlers.value(reply->nameSpace());

        if (!QMetaObject::invokeMethod(handler, QString("process" + reply->method()).toLatin1().data(), Q_ARG(QVariantMap, data)))
            qWarning() << "JsonRpc: method not implemented:" << reply->method();

        return;
    }

    // check if this is a notification
    if (data.contains("notification")) {
        QStringList notification = data.value("notification").toString().split(".");
        QString nameSpace = notification.first();
        QString method = notification.last();
        JsonHandler *handler = m_handlers.value(nameSpace);

        if (!handler) {
            qWarning() << "JsonRpc: handler not implemented:" << nameSpace;
            return;
        }

        if (!QMetaObject::invokeMethod(handler, QString("process" + method).toLatin1().data(), Q_ARG(QVariantMap, data)))
            qWarning() << "method not implemented";

    }
}



JsonRpcReply::JsonRpcReply(int commandId, QString nameSpace, QString method, QVariantMap params, QObject *parent):
    QObject(parent),
    m_commandId(commandId),
    m_nameSpace(nameSpace),
    m_method(method),
    m_params(params)
{
}

int JsonRpcReply::commandId() const
{
    return m_commandId;
}

QString JsonRpcReply::nameSpace() const
{
    return m_nameSpace;
}

QString JsonRpcReply::method() const
{
    return m_method;
}

QVariantMap JsonRpcReply::params() const
{
    return m_params;
}

QVariantMap JsonRpcReply::requestMap()
{
    QVariantMap request;
    request.insert("id", m_commandId);
    request.insert("method", m_nameSpace + "." + m_method);
    if (!m_params.isEmpty())
        request.insert("params", m_params);

    return request;
}
