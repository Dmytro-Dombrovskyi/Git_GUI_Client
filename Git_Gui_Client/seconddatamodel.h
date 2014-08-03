#ifndef SECONDDATAMODEL_H
#define SECONDDATAMODEL_H

#include <QAbstractTableModel>
#include "gitdata.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The SecondDataModel class
/// Data model for tableView_2
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SecondDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SecondDataModel (const QStringList dataList, QObject *parent = 0);
    QVariant data            (const QModelIndex & index, int nRole) const;
    int      rowCount        (const QModelIndex &) const {return numRows_;}
    int      columnCount     (const QModelIndex &) const {return numColumns_;}
    QVariant headerData      (int section, Qt::Orientation orientation, int role) const;
    virtual  ~SecondDataModel();

private:    
    QVector<revision_files*> revFiles_;
    unsigned int numRows_;
    unsigned int numColumns_;
    enum        {
                 FILE_NAME,
                 FILE_ACTION,
                 NUM_COLUMNS
                };
};

#endif // SECONDDATAMODEL_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
