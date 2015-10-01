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

#include "vendors.h"

#include <QDebug>

Vendors::Vendors(QObject *parent) :
    QAbstractListModel(parent)
{
}

QList<Vendor> Vendors::vendors()
{
    return m_vendors;
}

int Vendors::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_vendors.count();
}

QVariant Vendors::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_vendors.count())
        return QVariant();

    Vendor vendor = m_vendors.at(index.row());
    if (role == NameRole) {
        return vendor.name();
    } else if (role == IdRole) {
        return vendor.id().toString();
    }
    return QVariant();
}

void Vendors::addVendor(Vendor vendor)
{
    beginInsertRows(QModelIndex(), m_vendors.count(), m_vendors.count());
    qDebug() << "Vendors: loaded vendor" << vendor.name();
    m_vendors.append(vendor);
    endInsertRows();
}

void Vendors::clearModel()
{
    beginResetModel();
    m_vendors.clear();
    endResetModel();
}

QHash<int, QByteArray> Vendors::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IdRole] = "id";
    return roles;
}
