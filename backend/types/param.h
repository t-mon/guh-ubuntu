#ifndef PARAM_H
#define PARAM_H

#include <QObject>
#include <QString>
#include <QVariant>

class Param
{
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QVariant value READ value CONSTANT)

public:
    Param(const QString &name = QString(), const QVariant &value = QVariant());

    QString name() const;
    void setName(const QString &name);

    QVariant value() const;
    void setValue(const QVariant &value);

private:
    QString m_name;
    QVariant m_value;

};

#endif // PARAM_H
