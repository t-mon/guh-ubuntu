#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QUuid>

#include "param.h"

class Device : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QUuid id READ id CONSTANT)
    Q_PROPERTY(QUuid deviceClassId READ deviceClassId CONSTANT)
    Q_PROPERTY(bool setupComplete READ setupComplete WRITE setSetupComplete NOTIFY setupCompleteChanged)

public:
    explicit Device(QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QUuid id() const;
    void setId(const QUuid &id);

    QUuid deviceClassId() const;
    void setDeviceClassId(const QUuid &deviceClassId);

    QList<Param> params() const;
    void setParams(const QList<Param> params);

    bool setupComplete();
    void setSetupComplete(const bool &setupComplete);

private:
    QString m_name;
    QUuid m_id;
    QUuid m_deviceClassId;
    QList<Param> m_params;
    bool m_setupComplete;

signals:
    void nameChanged();
    void setupCompleteChanged();

};

#endif // DEVICE_H
