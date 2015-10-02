#include "device.h"

Device::Device(QObject *parent) :
    QObject(parent)
{
}

QString Device::name() const
{
    return m_name;
}

void Device::setName(const QString &name)
{
    m_name = name;
    emit nameChanged();
}

QUuid Device::id() const
{
    return m_id;
}

void Device::setId(const QUuid &id)
{
    m_id = id;
}

QUuid Device::deviceClassId() const
{
    return m_deviceClassId;
}

void Device::setDeviceClassId(const QUuid &deviceClassId)
{
    m_deviceClassId = deviceClassId;
}

QList<Param> Device::params() const
{
    return m_params;
}

void Device::setParams(const QList<Param> params)
{
    m_params = params;
}

bool Device::setupComplete()
{
    return m_setupComplete;
}

void Device::setSetupComplete(const bool &setupComplete)
{
    m_setupComplete = setupComplete;
    emit setupCompleteChanged();
}
