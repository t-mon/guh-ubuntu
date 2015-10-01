#ifndef DEVICECLASSFILERMODEL_H
#define DEVICECLASSFILERMODEL_H

#include <QSortFilterProxyModel>
#include <QUuid>

#include "deviceclasses.h"
#include "deviceclass.h"

class DeviceClassesFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QUuid vendorId READ vendorId WRITE setVendorId NOTIFY vendorIdChanged)
    Q_PROPERTY(DeviceClasses *deviceClasses READ deviceClasses CONSTANT)

public:
    explicit DeviceClassesFilterModel(QObject *parent = 0);

    QUuid vendorId() const;
    void setVendorId(const QUuid &vendorId);

    DeviceClasses *deviceClasses();
    void setDeviceClasses(DeviceClasses *deviceClasses);

    Q_INVOKABLE void resetFilter();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;

private:
    QUuid m_vendorId;
    DeviceClasses *m_deviceClasses;

signals:
    void vendorIdChanged();
    void deviceClassesChanged();

public slots:

};

#endif // DEVICECLASSFILERMODEL_H
