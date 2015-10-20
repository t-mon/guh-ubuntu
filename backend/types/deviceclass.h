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

#include <QObject>
#include <QUuid>
#include <QList>
#include <QString>

#include "paramtypes.h"

class DeviceClass : public QObject
{
    Q_OBJECT
    Q_ENUMS(CreateMethod)
    Q_ENUMS(SetupMethod)

    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QUuid id READ id CONSTANT)
    Q_PROPERTY(QUuid vendorId READ vendorId CONSTANT)
    Q_PROPERTY(ParamTypes *paramTypes READ paramTypes NOTIFY paramTypesChanged)
    Q_PROPERTY(ParamTypes *discoveryParamTypes READ discoveryParamTypes NOTIFY discoveryParamTypesChanged)
    Q_PROPERTY(QList<CreateMethod> createMethods READ createMethods CONSTANT)
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

    DeviceClass(QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QUuid id() const;
    void setId(const QUuid &id);

    QUuid vendorId() const;
    void setVendorId(const QUuid &vendorId);

    QUuid pluginId() const;
    void setPluginId(const QUuid &pluginId);

    QList<CreateMethod> createMethods() const;
    void setCreateMethods(QList<CreateMethod> createMethods);

    SetupMethod setupMethod() const;
    void setSetupMethod(SetupMethod setupMethod);

    ParamTypes *paramTypes() const;
    void setParamTypes(ParamTypes *paramTypes);

    ParamTypes *discoveryParamTypes() const;
    void setDiscoveryParamTypes(ParamTypes *paramTypes);

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

    ParamTypes *m_paramTypes;
    ParamTypes *m_discoveryParamTypes;

//    QList<StateType> m_stateTypes;
//    QList<EventType> m_eventTypes;
//    QList<ActionType> m_actionTypes;

signals:
    void paramTypesChanged();
    void discoveryParamTypesChanged();

};

#endif // DEVICECLASS_H
