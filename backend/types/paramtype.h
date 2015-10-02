#ifndef PARAMTYPE_H
#define PARAMTYPE_H

#include <QVariant>
#include <QDebug>

#include "types.h"

class ParamType
{
public:
    ParamType();
    ParamType(const QString &name, const QVariant::Type type, const QVariant &defaultValue = QVariant());

    QString name() const;
    void setName(const QString &name);

    QVariant::Type type() const;
    void setType(QVariant::Type type);

    QVariant defaultValue() const;
    void setDefaultValue(const QVariant &defaultValue);

    QVariant minValue() const;
    void setMinValue(const QVariant &minValue);

    QVariant maxValue() const;
    void setMaxValue(const QVariant &maxValue);

    Types::InputType inputType() const;
    void setInputType(const Types::InputType &inputType);

    Types::Unit unit() const;
    void setUnit(const Types::Unit &unit);

    QString unitString() const;
    void setUnitString(const QString &unitString);

    QList<QVariant> allowedValues() const;
    void setAllowedValues(const QList<QVariant> allowedValues);

    bool readOnly() const;
    void setReadOnly(const bool &readOnly);

private:
    QString m_name;
    QVariant::Type m_type;
    QVariant m_defaultValue;
    QVariant m_minValue;
    QVariant m_maxValue;
    Types::InputType m_inputType;
    Types::Unit m_unit;
    QString m_unitString;
    QVariantList m_allowedValues;
    bool m_readOnly;
};

#endif // PARAMTYPE_H
