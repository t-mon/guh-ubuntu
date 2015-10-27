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

#include "guhconnection.h"

GuhConnection::GuhConnection(QObject *parent) :
    QObject(parent)
{
}

QString GuhConnection::name() const
{
    return m_name;
}

void GuhConnection::setName(const QString &name)
{
    m_name = name;
}

QString GuhConnection::webSocketUrl() const
{
    return m_webSocketUrl;
}

void GuhConnection::setWebSocketUrl(const QString &webSocketUrl)
{
    m_webSocketUrl = webSocketUrl;
}

QString GuhConnection::hostAddress() const
{
    return m_hostAddress;
}

void GuhConnection::setHostAddress(const QString &hostAddress)
{
    m_hostAddress = hostAddress;
}

QUuid GuhConnection::uuid() const
{
    return m_uuid;
}

void GuhConnection::setUuid(const QUuid &uuid)
{
    m_uuid = uuid;
}


