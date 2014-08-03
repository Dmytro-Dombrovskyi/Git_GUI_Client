#include "seconddatamodel.h"

SecondDataModel::SecondDataModel(const QStringList dataList, QObject *parent) :
    QAbstractTableModel(parent)
{

    if(!dataList.isEmpty())
    {
        int count = 0;
        foreach(QString dataStr, dataList)
        {
            dataStr.simplified();
            if(!dataStr.isEmpty())
                revFiles_.append(new revision_files(dataStr));
//            else
//                qWarning() << "Warning!SecondDataModel constructor called! Data is empty in array list! Index: " + QString::number(count);
            ++count;
        }
    }

    if(!revFiles_.isEmpty())
        numRows_ = revFiles_.size();
    else
        numRows_ = 0;

    numColumns_ = NUM_COLUMNS;
}

SecondDataModel::~SecondDataModel()
{
    const int size = revFiles_.size();
    for(int i = 0; i < size; ++i)
    {
        delete revFiles_[i];
    }
}

QVariant SecondDataModel::data(const QModelIndex & index, int nRole) const
{
  if(!index.isValid()) return QVariant();
  QString returnData;// = findData(index);

  switch(index.column())
    {
    case FILE_NAME:     returnData = revFiles_.at(index.row())->get_fileName();
      break;
    case FILE_ACTION:   returnData = revFiles_.at(index.row())->get_fileAction();
      break;
    default:            qWarning() << "Fail return data";
    }
  return (nRole == Qt::DisplayRole) ? QVariant(returnData) : QVariant();
}


QVariant SecondDataModel::headerData(int section,
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
           case FILE_NAME:    Header = "File name";
               break;
           case FILE_ACTION:  Header = "File status";
               break;
           default:
               qWarning() << "Error, Couldn't set feader: " << Header;
               break;
           }
           return Header;
       }
       else
           return QVariant();
   }
   return QVariant();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

