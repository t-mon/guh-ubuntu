#ifndef DEVICES_H
#define DEVICES_H

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

#include <QAbstractListModel>

#include "device.h"

class Devices : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DeviceRole {
        NameRole = Qt::DisplayRole,
        DeviceNameRole,
        IdRole,
        DeviceClassRole,
        SetupComplete
    };

    explicit Devices(QObject *parent = 0);

    QList<Device *> devices();

    Q_INVOKABLE int count() const;
    Q_INVOKABLE Device *get(int index) const;
    Q_INVOKABLE Device *getDevice(const QUuid &deviceId) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addDevice(Device *device);
    void removeDevice(Device *device);

    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Device *> m_devices;

};

#endif // DEVICES_H
