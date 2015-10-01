#ifndef JSONRPCCLIENT_H
#define JSONRPCCLIENT_H

#include <QObject>
#include <QVariantMap>

#include "devicehandler.h"

class JsonRpcReply;
class JsonHandler;

class JsonRpcClient : public QObject
{
    Q_OBJECT
public:
    explicit JsonRpcClient(QObject *parent = 0);

    void getVendors();
    void getDeviceClasses();

private:
    int m_id;
    QHash<QString, JsonHandler *> m_handlers;
    QHash<int, JsonRpcReply *> m_replies;

    DeviceHandler *m_deviceHandler;

    JsonRpcReply *createReply(QString nameSpace, QString method, QVariantMap params = QVariantMap());

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
