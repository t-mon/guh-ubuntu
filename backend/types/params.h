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

#ifndef PARAMS_H
#define PARAMS_H

#include <QAbstractListModel>

#include "param.h"

class Params : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ParamRole {
        NameRole = Qt::DisplayRole,
        ValueRole
    };

    explicit Params(QObject *parent = 0);

    QList<Param *> params();

    Q_INVOKABLE int count() const;
    Q_INVOKABLE Param *get(int index) const;
    Q_INVOKABLE Param *getParam(QString name) const;

    Q_INVOKABLE int paramCount() const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void addParam(Param *param);

    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Param *> m_params;

};

#endif // PARAMS_H
