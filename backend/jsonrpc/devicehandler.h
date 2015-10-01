#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include <QObject>

#include "jsonhandler.h"

class DeviceHandler : public JsonHandler
{
    Q_OBJECT
public:
    explicit DeviceHandler(QObject *parent = 0);

    QString nameSpace() const;

    Q_INVOKABLE void processGetSupportedVendors(const QVariantMap &params);

signals:

public slots:

};

#endif // DEVICEHANDLER_H
