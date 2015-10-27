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

#ifndef GUHCONNECTIONS_H
#define GUHCONNECTIONS_H

#include <QAbstractListModel>

#include "guhconnection.h"

class GuhConnections : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ConnectionRole {
        NameRole = Qt::DisplayRole,
        HostAddressRole,
        WebSocketUrlRole
    };

    explicit GuhConnections(QObject *parent = 0);

    Q_INVOKABLE GuhConnection *get(const QString &webSocketUrl);
    QList<GuhConnection *> guhConnections();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addConnection(const QString &name, const QString &hostAddress, const QString &webSocketUrl);
    Q_INVOKABLE void removeConnection(GuhConnection *guhConnection);

    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<GuhConnection *> m_connections;

};

#endif // GUHCONNECTIONS_H
