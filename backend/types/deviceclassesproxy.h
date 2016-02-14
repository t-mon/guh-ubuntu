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

#ifndef DEVICECLASSFILERMODEL_H
#define DEVICECLASSFILERMODEL_H

#include <QUuid>
#include <QObject>
#include <QSortFilterProxyModel>

#include "deviceclasses.h"
#include "deviceclass.h"

class DeviceClassesProxy : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QUuid vendorId READ vendorId WRITE setVendorId NOTIFY vendorIdChanged)
    Q_PROPERTY(DeviceClasses *deviceClasses READ deviceClasses CONSTANT)

public:
    explicit DeviceClassesProxy(QObject *parent = 0);

    QUuid vendorId() const;
    void setVendorId(const QUuid &vendorId);

    DeviceClasses *deviceClasses();
    void setDeviceClasses(DeviceClasses *deviceClasses);

    Q_INVOKABLE void resetFilter();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;

private:
    QUuid m_vendorId;
    DeviceClasses *m_deviceClasses;

signals:
    void vendorIdChanged();
    void deviceClassesChanged();

};

#endif // DEVICECLASSFILERMODEL_H
