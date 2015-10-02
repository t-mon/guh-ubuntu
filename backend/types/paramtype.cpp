#include "paramtype.h"

ParamType::ParamType()
{
    m_readOnly = false;
}

ParamType::ParamType(const QString &name, const QVariant::Type type, const QVariant &defaultValue) :
    m_name(name),
    m_type(type),
    m_defaultValue(defaultValue),
    m_readOnly(false)
{
}

QString ParamType::name() const
{
    return m_name;
}

void ParamType::setName(const QString &name)
{
    m_name = name;
}

QVariant::Type ParamType::type() const
{
    return m_type;
}

void ParamType::setType(QVariant::Type type)
{
    m_type = type;
}

QVariant ParamType::defaultValue() const
{
    return m_defaultValue;
}

void ParamType::setDefaultValue(const QVariant &defaultValue)
{
    m_defaultValue = defaultValue;
}

QVariant ParamType::minValue() const
{
    return m_minValue;
}

void ParamType::setMinValue(const QVariant &minValue)
{
    m_minValue = minValue;
}

QVariant ParamType::maxValue() const
{
    return m_maxValue;
}

void ParamType::setMaxValue(const QVariant &maxValue)
{
    m_maxValue = maxValue;
}

Types::InputType ParamType::inputType() const
{
    return m_inputType;
}

void ParamType::setInputType(const Types::InputType &inputType)
{
    m_inputType = inputType;
}

QString ParamType::unitString() const
{
    return m_unitString;
}

void ParamType::setUnitString(const QString &unitString)
{
    m_unitString = unitString;
}

Types::Unit ParamType::unit() const
{
    return m_unit;
}

void ParamType::setUnit(const Types::Unit &unit)
{
    m_unit = unit;
}

QList<QVariant> ParamType::allowedValues() const
{
    return m_allowedValues;
}

void ParamType::setAllowedValues(const QList<QVariant> allowedValues)
{
    m_allowedValues = allowedValues;
}

bool ParamType::readOnly() const
{
    return m_readOnly;
}

void ParamType::setReadOnly(const bool &readOnly)
{
    m_readOnly = readOnly;
}
