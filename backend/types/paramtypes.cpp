#include "paramtypes.h"

ParamTypes::ParamTypes(QObject *parent) :
    QAbstractListModel(parent)
{
}

QList<ParamType *> ParamTypes::paramTypes()
{
    return m_paramTypes;
}

ParamType *ParamTypes::get(int index) const
{
    return m_paramTypes.at(index);
}

ParamType *ParamTypes::getParamType(const QString &name) const
{
    foreach (ParamType *paramType, m_paramTypes) {
        if (paramType->name() == name) {
            return paramType;
        }
    }
    return 0;
}

int ParamTypes::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_paramTypes.count();
}

QVariant ParamTypes::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_paramTypes.count())
        return QVariant();

    ParamType *paramType = m_paramTypes.at(index.row());
    if (role == NameRole) {
        return paramType->name();
    } else if (role == TypeRole) {
        return paramType->type();
    } else if (role == DefaultValueRole) {
        return paramType->defaultValue();
    } else if (role == MinValueRole) {
        return paramType->minValue();
    } else if (role == MaxValueRole) {
        return paramType->maxValue();
    } else if (role == InputTypeRole) {
        return paramType->inputType();
    } else if (role == UnitStringRole) {
        return paramType->unitString();
    } else if (role == AllowedValuesRole) {
        return paramType->allowedValues();
    } else if (role == ReadOnlyRole) {
        return paramType->readOnly();
    }
    return QVariant();
}

void ParamTypes::addParamType(ParamType *paramType)
{
    beginInsertRows(QModelIndex(), m_paramTypes.count(), m_paramTypes.count());
    qDebug() << "ParamTypes: loaded paramType" << paramType->name();
    m_paramTypes.append(paramType);
    endInsertRows();
}

void ParamTypes::clearModel()
{
    beginResetModel();
    m_paramTypes.clear();
    endResetModel();
}

QHash<int, QByteArray> ParamTypes::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[TypeRole] = "type";
    roles[MinValueRole] = "minValue";
    roles[MaxValueRole] = "maxValue";
    roles[InputTypeRole] = "inputType";
    roles[UnitStringRole] = "unitString";
    roles[AllowedValuesRole] = "allowedValues";
    roles[ReadOnlyRole] = "readOnly";
    return roles;
}
