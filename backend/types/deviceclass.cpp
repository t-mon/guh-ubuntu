#include "deviceclass.h"

#include <QDebug>

DeviceClass::DeviceClass()
{
}

QUuid DeviceClass::id() const
{
    return m_id;
}

void DeviceClass::setId(const QUuid &id)
{
    m_id = id;
}

QUuid DeviceClass::vendorId() const
{
    return m_vendorId;
}

void DeviceClass::setVendorId(const QUuid &vendorId)
{
    m_vendorId = vendorId;
}

QUuid DeviceClass::pluginId() const
{
    return m_pluginId;
}

void DeviceClass::setPluginId(const QUuid &pluginId)
{
    m_pluginId = pluginId;
}

QString DeviceClass::name() const
{
    return m_name;
}

void DeviceClass::setName(const QString &name)
{
    m_name = name;
}
