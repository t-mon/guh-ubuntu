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

#ifndef PLUGINS_H
#define PLUGINS_H

#include <QObject>
#include <QAbstractListModel>

#include "plugin.h"

class Plugins : public QAbstractListModel
{
    Q_OBJECT
public:
    enum StateRole {
        NameRole = Qt::DisplayRole,
        PluginIdRole
    };

    explicit Plugins(QObject *parent = 0);

    QList<Plugin *> plugins();

    Q_INVOKABLE int count() const;
    Q_INVOKABLE Plugin *get(int index) const;
    Q_INVOKABLE Plugin *getPlugin(const QUuid &pluginId) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addPlugin(Plugin *plugin);

    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Plugin *> m_plugins;

};

#endif // PLUGINS_H
