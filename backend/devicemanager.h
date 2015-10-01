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

#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>

#include "types/vendors.h"
#include "types/deviceclasses.h"
#include "types/deviceclassesfiltermodel.h"

class DeviceManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Vendors *vendors READ vendors CONSTANT)
    Q_PROPERTY(DeviceClasses *deviceClasses READ deviceClasses CONSTANT)
    Q_PROPERTY(DeviceClassesFilterModel *deviceClassesFilter READ deviceClassesFilter CONSTANT)

public:
    explicit DeviceManager(QObject *parent = 0);

    Vendors *vendors();
    DeviceClasses *deviceClasses();
    DeviceClassesFilterModel *deviceClassesFilter();

private:
    Vendors *m_vendors;
    DeviceClasses *m_deviceClasses;
    DeviceClassesFilterModel *m_deviceClassesFilter;

public slots:

};

#endif // DEVICEMANAGER_H
