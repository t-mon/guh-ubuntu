#ifndef LOGGINGHANDLER_H
#define LOGGINGHANDLER_H

#include <QObject>

#include "jsonhandler.h"

class LoggingHandler : public JsonHandler
{
    Q_OBJECT
public:
    explicit LoggingHandler(QObject *parent = 0);

    QString nameSpace() const;

    Q_INVOKABLE void processLogEntryAdded(const QVariantMap &params);
    Q_INVOKABLE void processLogDatabaseUpdated(const QVariantMap &params);

};

#endif // LOGGINGHANDLER_H
