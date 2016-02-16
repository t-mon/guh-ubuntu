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

#ifndef PARAMTYPES_H
#define PARAMTYPES_H

#include <QAbstractListModel>

#include "paramtype.h"

class ParamTypes : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ParamTypeRole {
        NameRole = Qt::DisplayRole,
        TypeRole,
        DefaultValueRole,
        MinValueRole,
        MaxValueRole,
        InputTypeRole,
        UnitStringRole,
        AllowedValuesRole,
        ReadOnlyRole
    };

    explicit ParamTypes(QObject *parent = 0);

    QList<ParamType *> paramTypes();

    Q_INVOKABLE int count() const;
    Q_INVOKABLE ParamType *get(int index) const;
    Q_INVOKABLE ParamType *getParamType(const QString &name) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addParamType(ParamType *paramType);

    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<ParamType *> m_paramTypes;
};

#endif // PARAMTYPES_H
