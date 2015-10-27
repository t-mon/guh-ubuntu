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

#ifndef EVENTTYPES_H
#define EVENTTYPES_H

#include <QObject>
#include <QAbstractListModel>

#include "eventtype.h"

class EventTypes : public QAbstractListModel
{
    Q_OBJECT

public:
    enum EventTypeRole {
        NameRole,
        IdRole
    };

    EventTypes(QObject *parent = 0);

    QList<EventType *> eventTypes();

    Q_INVOKABLE EventType *get(int index) const;
    Q_INVOKABLE EventType *getEventType(const QUuid &eventTypeId) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addEventType(EventType *eventType);

    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<EventType *> m_eventTypes;

};

#endif // EVENTTYPES_H
