#ifndef MY_DATA_MODEL_H
#define MY_DATA_MODEL_H

#include <QAbstractTableModel>
//#include <>
#include "gitdata.h"

class My_Data_Model : public QAbstractTableModel
{
  Q_OBJECT
private:
  QVector<GitData*> myDataItem_;
  unsigned int numberRows_;
  unsigned int numberColumns_;

public:
  explicit My_Data_Model(const QVector<GitData*> myDataInit,
                         QObject *parent = 0);
  QVariant data(const QModelIndex & index, int nRole) const;
  int rowCount(const QModelIndex &) const {return numberRows_;}
  int columnCount(const QModelIndex &) const {return numberColumns_;}
  //QString findData(const QModelIndex&indexRowColumn)const;
  virtual ~My_Data_Model() { }
signals:

public slots:


};

#endif // MY_DATA_MODEL_H
