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

#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include <QObject>

#include "jsonhandler.h"

class DeviceHandler : public JsonHandler
{
    Q_OBJECT
public:
    explicit DeviceHandler(QObject *parent = 0);

    QString nameSpace() const;

    // Get methods
    Q_INVOKABLE void processGetSupportedVendors(const QVariantMap &params);
    Q_INVOKABLE void processGetSupportedDevices(const QVariantMap &params);
    Q_INVOKABLE void processGetConfiguredDevices(const QVariantMap &params);

    Q_INVOKABLE void processRemoveConfiguredDevice(const QVariantMap &params);
    Q_INVOKABLE void processAddConfiguredDevice(const QVariantMap &params);
    Q_INVOKABLE void processGetDiscoveredDevices(const QVariantMap &params);


    // Notifications
    Q_INVOKABLE void processDeviceRemoved(const QVariantMap &params);
    Q_INVOKABLE void processDeviceAdded(const QVariantMap &params);


signals:

public slots:

};

#endif // DEVICEHANDLER_H
