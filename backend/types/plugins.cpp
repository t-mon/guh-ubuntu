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

#include "plugins.h"

#include <QDebug>

Plugins::Plugins(QObject *parent) :
    QAbstractListModel(parent)
{

}

QList<Plugin *> Plugins::plugins()
{
    return m_plugins;
}

int Plugins::count() const
{
    return m_plugins.count();
}

Plugin *Plugins::get(int index) const
{
    return m_plugins.at(index);
}

Plugin *Plugins::getPlugin(const QUuid &pluginId) const
{
    foreach (Plugin *plugin, m_plugins) {
        if (plugin->pluginId() == pluginId) {
            return plugin;
        }
    }
    return 0;
}

int Plugins::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_plugins.count();
}

QVariant Plugins::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_plugins.count())
        return QVariant();

    Plugin *plugin = m_plugins.at(index.row());
    if (role == NameRole) {
        return plugin->name();
    } else if (role == PluginIdRole) {
        return plugin->pluginId();
    }
    return QVariant();
}

void Plugins::addPlugin(Plugin *plugin)
{
    beginInsertRows(QModelIndex(), m_plugins.count(), m_plugins.count());
    //qDebug() << "Plugin: loaded plugin" << plugin->name();
    m_plugins.append(plugin);
    endInsertRows();
}

void Plugins::clearModel()
{
    beginResetModel();
    qDebug() << "Plugins: delete all plugins";
    qDeleteAll(m_plugins);
    m_plugins.clear();
    endResetModel();
}

QHash<int, QByteArray> Plugins::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[PluginIdRole] = "pluginId";
    return roles;
}

