#include "vendorsproxy.h"

#include <QDebug>

VendorsProxy::VendorsProxy(QObject *parent) : QSortFilterProxyModel(parent)
{

}

Vendors *VendorsProxy::vendors()
{
    return m_vendors;
}

void VendorsProxy::setVendors(Vendors *vendors)
{
    m_vendors = vendors;
    setSourceModel(vendors);
    sort(0);
}

bool VendorsProxy::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftName = sourceModel()->data(left);
    QVariant rightName = sourceModel()->data(right);

    return QString::localeAwareCompare(leftName.toString(), rightName.toString()) < 0;
}

