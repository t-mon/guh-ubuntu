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

#include "guhinterface.h"
#include "core.h"

#include <QGuiApplication>
#include <QJsonDocument>
#include <QJsonParseError>

GuhInterface::GuhInterface(QObject *parent) :
    QObject(parent)
{
    m_socket = new QWebSocket(QGuiApplication::applicationName(), QWebSocketProtocol::Version13, this);

    connect(m_socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(m_socket, SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessageReceived(QString)));
}

void GuhInterface::connectGuh(const QString &urlString)
{
    m_webSocketUrl = urlString;
    m_socket->open(QUrl(urlString));
}

void GuhInterface::sendData(const QByteArray &data)
{
    m_socket->sendTextMessage(QString::fromUtf8(data));
}

void GuhInterface::sendRequest(const QVariantMap &request)
{
    sendData(QJsonDocument::fromVariant(request).toJson());
}

bool GuhInterface::connected() const
{
    return m_connected;
}

void GuhInterface::setConnected(const bool &connected)
{
    m_connected = connected;
    emit connectedChanged();
}

void GuhInterface::onConnected()
{
    Core::instance()->discovery()->stopDiscovery();
    qDebug() << "Connected to" << m_webSocketUrl;

    setConnected(true);

    Core::instance()->connections()->addConnection("guhd", m_socket->peerAddress().toString(), m_webSocketUrl);
    Core::instance()->jsonRpcClient()->getVendors();
}

void GuhInterface::onDisconnected()
{
    qDebug() << "Disconnected from" << m_webSocketUrl << ": reason:" << m_socket->closeReason();
    setConnected(false);
}

void GuhInterface::onTextMessageReceived(const QString &data)
{
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Could not parse json data from guh" << data << error.errorString();
        return;
    }
    emit dataReady(jsonDoc.toVariant().toMap());
}

void GuhInterface::onError(QAbstractSocket::SocketError error)
{
    qWarning() << "Websocket error:" << error << m_socket->errorString();
}
