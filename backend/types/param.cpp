#include "param.h"

Param::Param(const QString &name, const QVariant &value):
    m_name(name),
    m_value(value)
{
}

QString Param::name() const
{
    return m_name;
}

void Param::setName(const QString &name)
{
    m_name = name;
}

QVariant Param::value() const
{
    return m_value;
}

void Param::setValue(const QVariant &value)
{
    m_value = value;
}
