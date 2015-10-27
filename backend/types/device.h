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

#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QUuid>

#include "param.h"
#include "params.h"

class Device : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUuid id READ id CONSTANT)
    Q_PROPERTY(QUuid deviceClassId READ deviceClassId CONSTANT)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString deviceName READ deviceName WRITE setDeviceName NOTIFY nameChanged)
    Q_PROPERTY(bool setupComplete READ setupComplete NOTIFY setupCompleteChanged)
    Q_PROPERTY(Params *params READ params NOTIFY paramsChanged)

public:
    explicit Device(QObject *parent = 0);

    QString name() const;

    QString deviceName() const;
    void setDeviceName(const QString &deviceName);

    QUuid id() const;
    void setId(const QUuid &id);

    QUuid deviceClassId() const;
    void setDeviceClassId(const QUuid &deviceClassId);

    Params *params() const;
    void setParams(Params *params);

    bool setupComplete();
    void setSetupComplete(const bool &setupComplete);

private:
    QString m_name;
    QUuid m_id;
    QUuid m_deviceClassId;
    bool m_setupComplete;
    Params *m_params;

signals:
    void nameChanged();
    void paramsChanged();
    void setupCompleteChanged();

};

#endif // DEVICE_H
