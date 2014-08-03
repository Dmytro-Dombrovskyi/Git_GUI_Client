#ifndef MY_DATA_MODEL_H
#define MY_DATA_MODEL_H

#include <QAbstractTableModel>
#include "gitdata.h"
class Gui_Main_Window;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The My_Data_Model class
///  Main Table model class which store data
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class My_Data_Model : public QAbstractTableModel
{
  Q_OBJECT
protected:
  friend class Gui_Main_Window;

  QVector<GitData*> myDataItem_;  
  unsigned int      numberRows_;
  unsigned int      numberColumns_;

  enum            { AUTOR_EMAIL,
                    AUTOR_NAME,
                    COMMITER_NAME,
                    COMMITER_EMAIL,
                    COMMIT,
                    DATE,
                    DATE_PERIOD,
                    HASH
                  };
public:  
  My_Data_Model          (const QVector<QStringList>, QObject *parent = 0);
  QVariant data          (const QModelIndex & index, int nRole) const;
  int      rowCount      (const QModelIndex &) const {return numberRows_;}
  int      columnCount   (const QModelIndex &) const {return numberColumns_;}
  QVariant headerData    (int section, Qt::Orientation orientation, int role) const;
  virtual  ~My_Data_Model();

};

#endif // MY_DATA_MODEL_H

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
