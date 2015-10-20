#ifndef PARAMTYPES_H
#define PARAMTYPES_H

#include <QAbstractListModel>

#include "paramtype.h"

class ParamTypes : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ParamTypeRole {
        NameRole,
        TypeRole,
        DefaultValueRole,
        MinValueRole,
        MaxValueRole,
        InputTypeRole,
        UnitStringRole,
        AllowedValuesRole,
        ReadOnlyRole
    };

    explicit ParamTypes(QObject *parent = 0);

    QList<ParamType *> paramTypes();

    Q_INVOKABLE ParamType *get(int index) const;
    Q_INVOKABLE ParamType *getParamType(const QString &name) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addParamType(ParamType *paramType);

    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<ParamType *> m_paramTypes;
};

#endif // PARAMTYPES_H
