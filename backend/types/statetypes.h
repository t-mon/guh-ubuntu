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

#ifndef STATETYPES_H
#define STATETYPES_H

#include <QObject>
#include <QAbstractListModel>

#include "statetype.h"

class StateTypes : public QAbstractListModel
{
public:
    enum StateTypeRole {
        NameRole,
        IdRole,
        TypeRole,
        DefaultValueRole,
        UnitStringRole
    };

    StateTypes(QObject *parent = 0);

    QList<StateType *> stateTypes();

    Q_INVOKABLE StateType *get(int index) const;
    Q_INVOKABLE StateType *getStateType(const QUuid &stateTypeId) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addStateType(StateType *stateType);

    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<StateType *> m_stateTypes;

};

#endif // STATETYPES_H
