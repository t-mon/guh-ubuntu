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

#ifndef VENDORMODEL_H
#define VENDORMODEL_H

#include <QAbstractListModel>

#include "vendor.h"

class VendorModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum VendorRole {
        NameRole,
        IdRole
    };

    explicit VendorModel(QObject *parent = 0);

    QList<Vendor> vendors();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addVendor(Vendor vendor);

    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Vendor> m_vendors;

//signals:
//    void vendorsChanged();

};

#endif // VENDORMODEL_H
