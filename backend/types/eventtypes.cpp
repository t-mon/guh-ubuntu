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

#include "eventtypes.h"

#include <QDebug>

EventTypes::EventTypes(QObject *parent) :
    QAbstractListModel(parent)
{
}

QList<EventType *> EventTypes::eventTypes()
{
    return m_eventTypes;
}

int EventTypes::count() const
{
    return m_eventTypes.count();
}

EventType *EventTypes::get(int index) const
{
    return m_eventTypes.at(index);
}

EventType *EventTypes::getEventType(const QUuid &eventTypeId) const
{
    foreach (EventType *eventType, m_eventTypes) {
        if (eventType->id() == eventTypeId) {
            return eventType;
        }
    }
    return 0;
}

int EventTypes::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_eventTypes.count();
}

QVariant EventTypes::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_eventTypes.count())
        return QVariant();

    EventType *eventType = m_eventTypes.at(index.row());
    if (role == NameRole) {
        return eventType->name();
    } else if (role == IdRole) {
        return eventType->id().toString();
    }
    return QVariant();
}

void EventTypes::addEventType(EventType *eventType)
{
    beginInsertRows(QModelIndex(), m_eventTypes.count(), m_eventTypes.count());
    qDebug() << "EventTypes: loaded eventType" << eventType->name();
    m_eventTypes.append(eventType);
    endInsertRows();
}

void EventTypes::clearModel()
{
    beginResetModel();
    m_eventTypes.clear();
    endResetModel();
}

QHash<int, QByteArray> EventTypes::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IdRole] = "id";
    return roles;
}

