#ifndef VENDORSPROXY_H
#define VENDORSPROXY_H

#include <QObject>
#include <QSortFilterProxyModel>

#include "vendors.h"

class VendorsProxy : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(Vendors *vendors READ vendors CONSTANT)

public:
    explicit VendorsProxy(QObject *parent = 0);

    Vendors *vendors();
    void setVendors(Vendors *vendors);

private:
    Vendors *m_vendors;

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;



public slots:
};

#endif // VENDORSPROXY_H
