#ifndef DEVICECLASS_H
#define DEVICECLASS_H

#include <QUuid>
#include <QList>
#include <QString>

class DeviceClass
{
public:

    enum CreateMethod {
        CreateMethodUser,
        CreateMethodAuto,
        CreateMethodDiscovery
    };
    Q_DECLARE_FLAGS(CreateMethods, CreateMethod)

    enum SetupMethod {
        SetupMethodJustAdd,
        SetupMethodDisplayPin,
        SetupMethodEnterPin,
        SetupMethodPushButton
    };

    DeviceClass();

    QUuid id() const;
    void setId(const QUuid &id);

    QUuid vendorId() const;
    void setVendorId(const QUuid &vendorId);

    QUuid pluginId() const;
    void setPluginId(const QUuid &pluginId);

    QString name() const;
    void setName(const QString &name);

//    QList<StateType> stateTypes() const;
//    void setStateTypes(const QList<StateType> &stateTypes);

//    QList<EventType> eventTypes() const;
//    void setEventTypes(const QList<EventType> &eventTypes);

//    QList<ActionType> actionTypes() const;
//    void setActionTypes(const QList<ActionType> &actionTypes);

//    QList<ParamType> paramTypes() const;
//    void setParamTypes(const QList<ParamType> &paramTypes);

//    QList<ParamType> discoveryParamTypes() const;
//    void setDiscoveryParamTypes(const QList<ParamType> &paramTypes);

//    CreateMethods createMethods() const;
//    void setCreateMethods(CreateMethods createMethods);

//    SetupMethod setupMethod() const;
//    void setSetupMethod(SetupMethod setupMethod);

//    QString pairingInfo() const;
//    void setPairingInfo(const QString &pairingInfo);

//    bool operator==(const DeviceClass &device) const;

private:
    QUuid m_id;
    QUuid m_vendorId;
    QUuid m_pluginId;
    QString m_name;
//    QList<StateType> m_stateTypes;
//    QList<EventType> m_eventTypes;
//    QList<EventType> m_allEventTypes;
//    QList<ActionType> m_actionTypes;
//    QList<ParamType> m_paramTypes;
//    QList<ParamType> m_discoveryParamTypes;
//    CreateMethods m_createMethods;
//    SetupMethod m_setupMethod;
//    QString m_pairingInfo;
};

#endif // DEVICECLASS_H
