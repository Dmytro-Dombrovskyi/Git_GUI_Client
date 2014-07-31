#include "my_data_model.h"

My_Data_Model::My_Data_Model(const QVector<GitData *> myDataInit, QObject *parent) :
  QAbstractTableModel(parent)
{
  if(!myDataInit.isEmpty())
    {
      int dataSize = myDataInit.size();
      for(int i = 0; i < dataSize; ++i)
        {
          myDataItem_.append(myDataInit.at(i));
        }
      numberRows_ = myDataItem_.size();
      numberColumns_ = myDataItem_.at(0)->get_size();
    }
}

QVariant My_Data_Model::data(const QModelIndex & index, int nRole) const
{
  if(!index.isValid()) return QVariant();
  QString returnData;// = findData(index);

  switch(index.column())
    {
    case 0:
       returnData = myDataItem_.at(index.row())->get_autorEmail();
      break;
    case 1:
       returnData = myDataItem_.at(index.row())->get_autorName();
      break;
    case 2:
       returnData = myDataItem_.at(index.row())->get_commiterName();
      break;
    case 3:
       returnData = myDataItem_.at(index.row())->get_commiter_Email();
      break;
    case 4:
       returnData = myDataItem_.at(index.row())->get_commitMessage();
      break;
    case 5:
       returnData = myDataItem_.at(index.row())->get_date();
      break;
    case 6:
       returnData = myDataItem_.at(index.row())->get_datePeriod();
      break;
    case 7:
       returnData = myDataItem_.at(index.row())->get_hash();
      break;
    default:
      qDebug() << "Fail return data";
    }
  return (nRole == Qt::DisplayRole) ? QVariant(returnData) : QVariant();
}

