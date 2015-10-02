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

#ifndef JSONTYPES_H
#define JSONTYPES_H

#include <QObject>
#include <QJsonDocument>
#include <QVariant>
#include <QUuid>

#include "../types/types.h"
#include "../types/deviceclass.h"
#include "../types/paramtype.h"

class Vendor;

class JsonTypes : public QObject
{
    Q_OBJECT
public:
    explicit JsonTypes(QObject *parent = 0);

    static Vendor unpackVendor(const QVariantMap &vendorMap);
    static DeviceClass unpackDeviceClass(const QVariantMap &deviceClassMap);
    static ParamType unpackParamType(const QVariantMap &paramTypeMap);


private:
    static DeviceClass::SetupMethod stringToSetupMethod(const QString &setupMethodString);
    static DeviceClass::CreateMethod stringToCreateMethod(const QString &createMethodString);
    static QPair<Types::Unit, QString> stringToUnit(const QString &unitString);
    static Types::InputType stringToInputType(const QString &inputTypeString);



signals:

public slots:

};

#endif // JSONTYPES_H
