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

#include "params.h"

#include <QDebug>

Params::Params(QObject *parent) :
    QAbstractListModel(parent)
{
}

QList<Param *> Params::params()
{
    return m_params;
}

int Params::count() const
{
    return m_params.count();
}

Param *Params::get(int index) const
{
    return m_params.at(index);
}

Param *Params::getParam(QString name) const
{
    foreach (Param *param, m_params) {
        if (param->name() == name) {
            return param;
        }
    }
    return 0;
}

int Params::paramCount() const
{
    return m_params.count();
}

int Params::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_params.count();
}

QVariant Params::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_params.count())
        return QVariant();

    Param *param = m_params.at(index.row());
    if (role == NameRole) {
        return param->name();
    } else if (role == ValueRole) {
        return param->value();
    }
    return QVariant();
}

void Params::addParam(Param *param)
{
    beginInsertRows(QModelIndex(), m_params.count(), m_params.count());
    //qDebug() << "Params: loaded param" << param->name();
    m_params.append(param);
    endInsertRows();
}

void Params::clearModel()
{
    beginResetModel();
    m_params.clear();
    endResetModel();
}

QHash<int, QByteArray> Params::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ValueRole] = "value";
    return roles;
}
