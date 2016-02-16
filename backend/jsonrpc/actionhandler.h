#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H

#include <QObject>

#include "jsonhandler.h"

class ActionHandler : public JsonHandler
{
    Q_OBJECT
public:
    explicit ActionHandler(QObject *parent = 0);

    QString nameSpace() const;

    Q_INVOKABLE void processExecuteAction(const QVariantMap &params);

signals:

public slots:
};

#endif // ACTIONHANDLER_H
