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

#include "statetypes.h"

#include <QDebug>

StateTypes::StateTypes(QObject *parent) :
    QAbstractListModel(parent)
{
}

QList<StateType *> StateTypes::stateTypes()
{
    return m_stateTypes;
}

int StateTypes::count() const
{
    return m_stateTypes.count();
}

StateType *StateTypes::get(int index) const
{
    return m_stateTypes.at(index);
}

StateType *StateTypes::getStateType(const QUuid &stateTypeId) const
{
    foreach (StateType *stateType, m_stateTypes) {
        if (stateType->id() == stateTypeId) {
            return stateType;
        }
    }
    return 0;
}

int StateTypes::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_stateTypes.count();
}

QVariant StateTypes::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_stateTypes.count())
        return QVariant();

    StateType *stateType = m_stateTypes.at(index.row());
    if (role == NameRole) {
        return stateType->name();
    } else if (role == IdRole) {
        return stateType->id().toString();
    } else if (role == TypeRole) {
        return stateType->type();
    } else if (role == DefaultValueRole) {
        return stateType->defaultValue();
    } else if (role == UnitStringRole) {
        return stateType->unitString();
    } else if (role == UnitRole) {
        return stateType->unit();
    }
    return QVariant();
}

void StateTypes::addStateType(StateType *stateType)
{
    beginInsertRows(QModelIndex(), m_stateTypes.count(), m_stateTypes.count());
    qDebug() << "StateTypes: loaded stateType" << stateType->name();
    m_stateTypes.append(stateType);
    endInsertRows();
}

void StateTypes::clearModel()
{
    beginResetModel();
    qDebug() << "StateTypes: delete all stateTypes";
    qDeleteAll(m_stateTypes);
    m_stateTypes.clear();
    endResetModel();
}

QHash<int, QByteArray> StateTypes::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IdRole] = "id";
    roles[TypeRole] = "type";
    roles[DefaultValueRole] = "defaultValue";
    roles[UnitStringRole] = "unitString";
    roles[UnitRole] = "unit";
    return roles;
}

