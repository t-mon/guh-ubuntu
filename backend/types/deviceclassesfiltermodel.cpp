#include "deviceclassesfiltermodel.h"

#include <QDebug>

DeviceClassesFilterModel::DeviceClassesFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

QUuid DeviceClassesFilterModel::vendorId() const
{
    return m_vendorId;
}

void DeviceClassesFilterModel::setVendorId(const QUuid &vendorId)
{
    m_vendorId = vendorId;
    emit vendorIdChanged();

    qDebug() << "DeviceClassesFilter: set vendorId to" << vendorId;

    invalidateFilter();
}

DeviceClasses *DeviceClassesFilterModel::deviceClasses()
{
    return m_deviceClasses;
}

void DeviceClassesFilterModel::setDeviceClasses(DeviceClasses *deviceClasses)
{
    m_deviceClasses = deviceClasses;
    setSourceModel(deviceClasses);
    emit deviceClassesChanged();
}

void DeviceClassesFilterModel::resetFilter()
{
    setVendorId(QUuid());
    invalidateFilter();
}

bool DeviceClassesFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    Q_UNUSED(sourceParent)

    DeviceClass deviceClass = m_deviceClasses->get(sourceRow);
    if (!m_vendorId.isNull() && deviceClass.vendorId() == m_vendorId) {
        qDebug() << "filter match" << deviceClass.name();
        return true;
    }

    return false;

}
