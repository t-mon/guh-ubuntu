#ifndef PARAMS_H
#define PARAMS_H

#include <QAbstractListModel>

#include "param.h"

class Params : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ParamRole {
        NameRole = Qt::DisplayRole,
        ValueRole
    };

    explicit Params(QObject *parent = 0);

    QList<Param *> params();

    Q_INVOKABLE int count() const;
    Q_INVOKABLE Param *get(int index) const;
    Q_INVOKABLE Param *getParam(QString name) const;

    Q_INVOKABLE int paramCount() const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void addParam(Param *param);

    void clearModel();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Param *> m_params;

};

#endif // PARAMS_H
