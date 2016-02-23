#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QObject>

#include "jsonhandler.h"

class EventHandler : public JsonHandler
{
    Q_OBJECT
public:
    explicit EventHandler(QObject *parent = 0);

    QString nameSpace() const;

    Q_INVOKABLE void processEventTriggered(const QVariantMap &params);

};

#endif // EVENTHANDLER_H
