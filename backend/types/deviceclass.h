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

#ifndef DEVICECLASS_H
#define DEVICECLASS_H

#include <QUuid>
#include <QList>
#include <QString>

#include <QMetaEnum>

#include "paramtype.h"

class DeviceClass
{
    Q_ENUMS(CreateMethod)
    Q_ENUMS(SetupMethod)
    Q_PROPERTY(QUuid id READ id CONSTANT)
    Q_PROPERTY(QUuid vendorId READ vendorId CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QList<CreateMethod> createMethods READ createMethods CONSTANT)
    Q_PROPERTY(SetupMethod setupMethod READ setupMethod CONSTANT)
    Q_PROPERTY(SetupMethod setupMethod READ setupMethod CONSTANT)


public:

    enum CreateMethod {
        CreateMethodUser,
        CreateMethodAuto,
        CreateMethodDiscovery
    };

    enum SetupMethod {
        SetupMethodJustAdd,
        SetupMethodDisplayPin,
        SetupMethodEnterPin,
        SetupMethodPushButton
    };

    DeviceClass();

    QUuid id() const;
    void setId(const QUuid &id);

    QUuid vendorId() const;
    void setVendorId(const QUuid &vendorId);

    QUuid pluginId() const;
    void setPluginId(const QUuid &pluginId);

    QString name() const;
    void setName(const QString &name);

    QList<CreateMethod> createMethods() const;
    void setCreateMethods(QList<CreateMethod> createMethods);

    SetupMethod setupMethod() const;
    void setSetupMethod(SetupMethod setupMethod);

    QList<ParamType> paramTypes() const;
    void setParamTypes(const QList<ParamType> &paramTypes);

    QList<ParamType> discoveryParamTypes() const;
    void setDiscoveryParamTypes(const QList<ParamType> &paramTypes);

//    QList<StateType> stateTypes() const;
//    void setStateTypes(const QList<StateType> &stateTypes);

//    QList<EventType> eventTypes() const;
//    void setEventTypes(const QList<EventType> &eventTypes);

//    QList<ActionType> actionTypes() const;
//    void setActionTypes(const QList<ActionType> &actionTypes);

private:
    QUuid m_id;
    QUuid m_vendorId;
    QUuid m_pluginId;
    QString m_name;
    QList<CreateMethod> m_createMethods;
    SetupMethod m_setupMethod;
    QList<ParamType> m_paramTypes;
    QList<ParamType> m_discoveryParamTypes;
//    QList<StateType> m_stateTypes;
//    QList<EventType> m_eventTypes;
//    QList<EventType> m_allEventTypes;
//    QList<ActionType> m_actionTypes;
};

#endif // DEVICECLASS_H
