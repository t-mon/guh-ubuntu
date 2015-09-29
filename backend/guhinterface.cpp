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

#include <QGuiApplication>

GuhInterface::GuhInterface(QObject *parent) :
    QObject(parent)
{
    m_socket = new QWebSocket(QGuiApplication::applicationName(), QWebSocketProtocol::Version13, this);

    connect(m_socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    connect(m_socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessageReceived(QByteArray)));
    connect(m_socket, SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessageReceived(QString)));
}

void GuhInterface::connectGuh(const QString &hostAddress)
{
    m_socket->open(QUrl("ws://" + hostAddress + ":4444"));
}

bool GuhInterface::connected() const
{
    return m_connected;
}

void GuhInterface::onConnected()
{
    m_connected = true;
    emit connectedChanged();

    qDebug() << "Connected to guh" << m_socket->peerAddress();
}

void GuhInterface::onDisconnected()
{
    m_connected = false;
    emit connectedChanged();

    qDebug() << "Disconnected from guh" << m_socket->peerAddress();
}

void GuhInterface::onBinaryMessageReceived(const QByteArray &data)
{
    qDebug() << data;
}

void GuhInterface::onTextMessageReceived(const QString &data)
{
    qDebug() << data;
}

void GuhInterface::onError(QAbstractSocket::SocketError error)
{
    qWarning() << "Websocket error:" << error << m_socket->errorString();
}
