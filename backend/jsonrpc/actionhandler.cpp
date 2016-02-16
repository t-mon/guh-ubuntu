#include "actionhandler.h"
#include <QDebug>

ActionHandler::ActionHandler(QObject *parent) :
    JsonHandler(parent)
{
}

QString ActionHandler::nameSpace() const
{
    return "Actions";
}

void ActionHandler::processExecuteAction(const QVariantMap &params)
{
    // response handled in the ui
    Q_UNUSED(params);
}

