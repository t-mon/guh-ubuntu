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
#include "../types/device.h"
#include "../types/deviceclass.h"
#include "../types/paramtype.h"
#include "../types/statetype.h"
#include "../types/eventtype.h"
#include "../types/actiontype.h"

class Vendor;

class JsonTypes : public QObject
{
    Q_OBJECT
public:
    explicit JsonTypes(QObject *parent = 0);

    static Vendor *unpackVendor(const QVariantMap &vendorMap, QObject *parent);
    static DeviceClass *unpackDeviceClass(const QVariantMap &deviceClassMap, QObject *parent);
    static Param *unpackParam(const QVariantMap &paramMap, QObject *parent);
    static ParamType *unpackParamType(const QVariantMap &paramTypeMap, QObject *parent);
    static StateType *unpackStateType(const QVariantMap &stateTypeMap, QObject *parent);
    static EventType *unpackEventType(const QVariantMap &eventTypeMap, QObject *parent);
    static ActionType *unpackActionType(const QVariantMap &actionTypeMap, QObject *parent);
    static Device *unpackDevice(const QVariantMap &deviceMap, QObject *parent);

private:
    static DeviceClass::SetupMethod stringToSetupMethod(const QString &setupMethodString);
    static DeviceClass::CreateMethod stringToCreateMethod(const QString &createMethodString);
    static QPair<Types::Unit, QString> stringToUnit(const QString &unitString);
    static Types::InputType stringToInputType(const QString &inputTypeString);



signals:

public slots:

};

#endif // JSONTYPES_H
