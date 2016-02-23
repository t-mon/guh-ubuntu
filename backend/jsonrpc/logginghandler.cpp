#include "logginghandler.h"

LoggingHandler::LoggingHandler(QObject *parent) :
    JsonHandler(parent)
{

}

QString LoggingHandler::nameSpace() const
{
    return "Logging";
}

void LoggingHandler::processLogEntryAdded(const QVariantMap &params)
{
    Q_UNUSED(params);
}

void LoggingHandler::processLogDatabaseUpdated(const QVariantMap &params)
{
    Q_UNUSED(params);
}

