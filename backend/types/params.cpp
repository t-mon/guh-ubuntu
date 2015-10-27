#include "params.h"

#include <QDebug>

Params::Params(QObject *parent) :
    QAbstractListModel(parent)
{
}

QList<Param *> Params::params()
{
    return m_params;
}

Param *Params::get(int index) const
{
    return m_params.at(index);
}

Param *Params::getParam(QString name) const
{
    foreach (Param *param, m_params) {
        if (param->name() == name) {
            return param;
        }
    }
    return 0;
}

int Params::paramCount() const
{
    return m_params.count();
}

int Params::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_params.count();
}

QVariant Params::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_params.count())
        return QVariant();

    Param *param = m_params.at(index.row());
    if (role == NameRole) {
        return param->name();
    } else if (role == ValueRole) {
        return param->value();
    }
    return QVariant();
}

void Params::addParam(Param *param)
{
    beginInsertRows(QModelIndex(), m_params.count(), m_params.count());
    //qDebug() << "Params: loaded param" << param->name();
    m_params.append(param);
    endInsertRows();
}

void Params::clearModel()
{
    beginResetModel();
    m_params.clear();
    endResetModel();
}

QHash<int, QByteArray> Params::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ValueRole] = "value";
    return roles;
}
