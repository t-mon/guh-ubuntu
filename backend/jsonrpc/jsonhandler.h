#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QObject>
#include <QDebug>

class JsonHandler : public QObject
{
    Q_OBJECT
public:
    explicit JsonHandler(QObject *parent = 0);

    virtual QString nameSpace() const = 0;

};

#endif // JSONHANDLER_H
