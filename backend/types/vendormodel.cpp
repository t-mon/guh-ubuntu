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

#include "vendormodel.h"

#include <QDebug>

VendorModel::VendorModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QList<Vendor> VendorModel::vendors()
{
    return m_vendors;
}

int VendorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_vendors.count();
}

QVariant VendorModel::data(const QModelIndex &index, int role) const
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

void VendorModel::addVendor(Vendor vendor)
{
    beginInsertRows(QModelIndex(), m_vendors.count(), m_vendors.count());
    qDebug() << "Vendors: add vendor" << vendor.name();
    m_vendors.append(vendor);
    endInsertRows();
}

void VendorModel::clearModel()
{
    beginResetModel();
    m_vendors.clear();
    endResetModel();
}

QHash<int, QByteArray> VendorModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IdRole] = "id";
    return roles;
}
