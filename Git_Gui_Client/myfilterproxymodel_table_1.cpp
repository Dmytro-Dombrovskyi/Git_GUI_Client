#include "myfilterproxymodel_table_1.h"
#include <QDate>
MyFilterProxyModel_Table_1::MyFilterProxyModel_Table_1(QObject *parent) :
  QSortFilterProxyModel(parent)
{
}
bool MyFilterProxyModel_Table_1::filterAcceptsColumn(int source_column,
                         const QModelIndex &source_parent
                         ) const
{
//    QModelIndex index_0 = sourceModel()->index(source_column, 0, source_parent);
//    QModelIndex index_1 = sourceModel()->index(source_column, 1, source_parent);
//    QModelIndex index_2 = sourceModel()->index(source_column, 2, source_parent);

//    return (sourceModel()->data(index_0).toString().contains(filterRegExp())
//                 || sourceModel()->data(index_1).toString().contains(filterRegExp()))
//                && dateInRange(sourceModel()->data(index_2).toDate());
//  return true;
}

bool MyFilterProxyModel_Table_1::lessThan(const QModelIndex &left,
                                          const QModelIndex &right
                                          ) const
{

}
