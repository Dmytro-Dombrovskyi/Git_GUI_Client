#ifndef MYFILTERPROXYMODEL_TABLE_1_H
#define MYFILTERPROXYMODEL_TABLE_1_H

#include <QSortFilterProxyModel>

class MyFilterProxyModel_Table_1 : public QSortFilterProxyModel
{
public:
  MyFilterProxyModel_Table_1(QObject *parent = 0);
  bool filterAcceptsColumn(int source_column,
                           const QModelIndex &source_parent
                           ) const;
  bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
};

#endif // MYFILTERPROXYMODEL_TABLE_1_H
