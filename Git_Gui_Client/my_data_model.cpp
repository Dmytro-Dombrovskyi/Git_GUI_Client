#include "my_data_model.h"
#include "gitdata.h"
#include <QMessageBox>

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
  this->setHeaderData(0, Qt::Horizontal, "Number", Qt::DisplayRole);
}

My_Data_Model::~My_Data_Model()
{
    int size = myDataItem_.size();
    for(int i = 0; i < size; ++i)
    {
        delete myDataItem_[i];
    }
}



// set data
QVariant My_Data_Model::data(const QModelIndex & index, int nRole) const
{
  if(!index.isValid()) return QVariant();
  QString returnData;// = findData(index);

  switch(index.column())
    {
    case AUTOR_EMAIL:     returnData = myDataItem_.at(index.row())->get_autorEmail();
      break;
    case AUTOR_NAME:      returnData = myDataItem_.at(index.row())->get_autorName();
      break;
    case COMMITER_NAME:   returnData = myDataItem_.at(index.row())->get_commiterName();
      break;
    case COMMITER_EMAIL:  returnData = myDataItem_.at(index.row())->get_commiter_Email();
      break;
    case COMMIT:          returnData = myDataItem_.at(index.row())->get_commitMessage();
      break;
    case DATE:            returnData = myDataItem_.at(index.row())->get_date();
      break;
    case DATE_PERIOD:     returnData = myDataItem_.at(index.row())->get_datePeriod();
      break;
    case HASH:            returnData = myDataItem_.at(index.row())->get_hash();
      break;
    default:              qDebug() << "Fail return data";

    }
  return (nRole == Qt::DisplayRole) ? QVariant(returnData) : QVariant();
}
// set header for columns
QVariant My_Data_Model::headerData(int section,
                    Qt::Orientation orientation,
                    int role
                    ) const
{
   if(role == Qt::DisplayRole)
   {
       if(orientation == Qt::Horizontal)
       {
           QString Header;
           switch (section)
           {
           case AUTOR_EMAIL:    Header = "Autor Email";
               break;
           case AUTOR_NAME:     Header = "Autor name";
               break;
           case COMMITER_NAME:  Header = "Commiter name";
               break;
           case COMMITER_EMAIL: Header = "Commiter e-mail";
               break;
           case COMMIT:         Header = "Commit";
               break;
           case DATE:           Header = "Date";
               break;
           case DATE_PERIOD:    Header = "Date period";
               break;
           case HASH:           Header = "SHA-1";
               break;
           default:
//               QMessageBox::critical(this, "Error", "Couldn't set header");
               qDebug() << "Error, Couldn't set feader: " << Header;
               break;
           }
           return Header;
       }
       else
           return QVariant();
   }
   return QVariant();
}
