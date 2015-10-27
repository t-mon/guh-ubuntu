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

#include "guhconnections.h"

#include <QUuid>
#include <QDebug>
#include <QSettings>

GuhConnections::GuhConnections(QObject *parent) :
    QAbstractListModel(parent)
{
    beginResetModel();
    QSettings settings;
    qDebug() << "Connections: loading connections " << settings.fileName();
    settings.beginGroup("Connections");
    foreach (const QString &uuid, settings.childGroups()) {
        settings.beginGroup(uuid);
        GuhConnection *connection = new GuhConnection(this);
        connection->setName(settings.value("name").toString());
        connection->setHostAddress(settings.value("hostAddress").toString());
        connection->setWebSocketUrl(settings.value("webSocketUrl").toString());
        connection->setUuid(QUuid(uuid));
        qDebug() << "    " << connection->webSocketUrl();
        m_connections.append(connection);
        settings.endGroup();
    }

    settings.endGroup();
    endResetModel();
}

GuhConnection *GuhConnections::get(const QString &webSocketUrl)
{
    foreach (GuhConnection *connection, m_connections) {
        if (connection->webSocketUrl() == webSocketUrl) {
            return connection;
        }
    }
    return NULL;
}

QList<GuhConnection *> GuhConnections::guhConnections()
{
    return m_connections;
}

int GuhConnections::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_connections.count();
}

QVariant GuhConnections::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_connections.count())
        return QVariant();

    GuhConnection *connection = m_connections.at(index.row());
    if (role == NameRole) {
        return connection->name();
    } else if (role == HostAddressRole) {
        return connection->hostAddress();
    } else if (role == WebSocketUrlRole) {
        return connection->webSocketUrl();
    }
    return QVariant();
}

void GuhConnections::addConnection(const QString &name, const QString &hostAddress, const QString &webSocketUrl)
{
    // check if we allready have added this connection
    foreach (GuhConnection *connection, m_connections) {
        if (connection->webSocketUrl() == webSocketUrl) {
            return;
        }
    }

    GuhConnection *connection = new GuhConnection(this);
    connection->setName(name);
    connection->setHostAddress(hostAddress);
    connection->setWebSocketUrl(webSocketUrl);
    connection->setUuid(QUuid::createUuid());

    qDebug() << "GuhConnections: add connection" << connection->webSocketUrl();
    beginInsertRows(QModelIndex(), m_connections.count(), m_connections.count());
    m_connections.append(connection);
    endInsertRows();

    QSettings settings;
    settings.beginGroup("Connections");
    settings.beginGroup(connection->uuid().toString());
    settings.setValue("name", name);
    settings.setValue("hostAddress", hostAddress);
    settings.setValue("webSocketUrl", webSocketUrl);
    settings.endGroup();
    settings.endGroup();
    qDebug() << "Connections: saved connection" << settings.fileName();
}

void GuhConnections::removeConnection(GuhConnection *guhConnection)
{
    int index = m_connections.indexOf(guhConnection);
    beginRemoveRows(QModelIndex(), index, index);
    qDebug() << "Connections: removed connection" << guhConnection->webSocketUrl();
    m_connections.removeAt(index);

    QSettings settings;
    settings.beginGroup("Connections");
    settings.remove(guhConnection->uuid().toString());
    settings.endGroup();
    guhConnection->deleteLater();
    endRemoveRows();
}

void GuhConnections::clearModel()
{
    beginResetModel();
    qDebug() << "GuhConnections: delete all connections";
    qDeleteAll(m_connections);
    m_connections.clear();
    endResetModel();
}

QHash<int, QByteArray> GuhConnections::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[HostAddressRole] = "hostAddress";
    roles[WebSocketUrlRole] = "webSocketUrl";
    return roles;
}
