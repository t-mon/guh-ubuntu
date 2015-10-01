#include "jsonrpcclient.h"
#include "../core.h"

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

JsonRpcReply *JsonRpcClient::createReply(QString nameSpace, QString method, QVariantMap params)
{
    m_id++;
    return new JsonRpcReply(m_id, nameSpace, method, params, this);
}

void JsonRpcClient::dataReceived(const QVariantMap &data)
{
    qDebug() << "data: " << QJsonDocument::fromVariant(data).toJson();
    int commandId = data.value("id").toInt();
    JsonRpcReply *reply = m_replies.take(commandId);

    if (reply) {
        qDebug() << "got response for" << QString("%1.%2").arg(reply->nameSpace(), reply->method());
        JsonHandler *handler = m_handlers.value(reply->nameSpace());

        if (!QMetaObject::invokeMethod(handler, QString("process" + reply->method()).toLatin1().data(), Q_ARG(QVariantMap, data)))
            qWarning() << "method not implemented";

        return;
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
