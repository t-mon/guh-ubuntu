#include "eventhandler.h"

EventHandler::EventHandler(QObject *parent) :
    JsonHandler(parent)
{

}

QString EventHandler::nameSpace() const
{
    return "Events";
}

void EventHandler::processEventTriggered(const QVariantMap &params)
{
    Q_UNUSED(params);
}

