#include "gitdata.h"
#include <QMessageBox>

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief GitData::GitData
/// \param initialData
/// constructor for class:
/// Parameters is List of strings:
/// Initialize data by index of strings in List
////////////////////////////////////////////////////////////////////////////////////////////////////////////
GitData::GitData(const QStringList &initialData, QObject *parent) : QObject(parent)
{
  if(!(initialData.isEmpty()))
    {
      unsigned int counter = 0;
      foreach(QString initialItem, initialData)
        {
          if(!(initialItem.isEmpty()))
              if(initialItem.contains('\"')) // delete '"' character from string(bag)
                {
                  initialItem.remove(QRegExp("\""));
                }
              GitDataInit(counter, initialItem);
          ++counter;
        }
    }  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief GitData::~GitData
/// Virtual Destructor
//////////////////////////////////////////////////////////////////////////////////////////////////////////
GitData::~GitData()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief GitData::GitDataInit
/// \param number
/// \param initialString
/// initial data in class by list index
////////////////////////////////////////////////////////////////////////////////////////////////////////
void GitData::GitDataInit(const unsigned int number, const QString &initialString)
{
  switch(number)
    {
    case AUTOR_EMAIL:    hash_          = initialString;
    break;
    case AUTOR_NAME:     autorName_     = initialString;
    break;
    case COMMITER_NAME:  autorEmail_    = initialString;
    break;
    case COMMITER_EMAIL: commiterEmail_ = initialString;
    break;
    case COMMIT:         commiterName_  = initialString;
    break;
    case DATE:           commitMessage_ = initialString;
    break;
    case DATE_PERIOD:    date_          = initialString;
    break;
    case HASH:           datePeriod_    = initialString;
    break;
  default:               qDebug() << "Initial error";
    return;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief GitData::set_revisionFiles
/// \param files
/// Set revisionFiles class
//////////////////////////////////////////////////////////////////////////////////////////////////////
//void GitData::set_revisionFiles(QString files)
//{
//  if(files.isEmpty()) return;

//  QStringList strings = files.split("\n");
//  foreach(QString current, strings)
//    {
//      revisionFiles_.append(new revision_files(current));
//    }
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief GitData::set...
/// \param init data
/// methods for setting class fields
/////////////////////////////////////////////////////////////////////////////////////////////////////
void GitData::set_hash(QString hash)
{
    if(hash.isEmpty() || (hash_ == hash)) return;
    hash_ = hash;
}

void GitData::set_autorName(QString autorName)
{
    if(autorName.isEmpty() || (autorName_ == autorName)) return;
    autorName_ = autorName;
}

void GitData::set_autorEmail(QString autorEmail)
{
    if(autorEmail.isEmpty() || autorEmail_ == autorEmail) return;
    autorEmail_ = autorEmail;
}

void GitData::set_commiterEmail(QString commiterEmail)
{
    if(commiterEmail.isEmpty() || commiterEmail_ == commiterEmail) return;
    commiterEmail_ = commiterEmail;
}

void GitData::set_commiterName(QString commiterName)
{
    if(commiterName.isEmpty() || commiterName_ == commiterName) return;
    commiterName_ = commiterName;
}

void GitData::set_commitMessage(QString commitMessage)
{
    if(commitMessage.isEmpty() || commitMessage_ == commitMessage) return;
    commitMessage_ = commitMessage;
}

void GitData::set_date(QString date)
{
    if(date.isEmpty() || date_ == date) return;
    date_ = date;
}

void GitData::set_datePeriod(QString datePeriod)
{
    if(datePeriod.isEmpty() || datePeriod_ == datePeriod) return;
    datePeriod_ = datePeriod;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief revision_files::revision_files
/// \param line
/// \param parent
/// Constructor for revision_files class
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
revision_files::revision_files(QString line, QObject * parent)
    : QObject(parent)
{
    if(!line.isEmpty())
    {
        QStringList itemsList = line.split("\t");
        if(itemsList.size() > CLASS_SIZE) qWarning() << itemsList;

        int count = 0;
        foreach(QString str, itemsList)
        {
            str.simplified();
            if(!str.isEmpty())
            {
                dataInit(str, count);
                ++count;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief dataInit
/// \param data
/// \param index
/// initialize data in class revision_files by index
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void revision_files::dataInit(const QString& data, const int index)
{
    if(data.isEmpty()) return;

    switch (index)
    {
        case FILE_ACTION:
        {
            switch(data.at(0).toLatin1())
            {
            case 65:
                fileAction_ = "Added";
                break;
            case 77:
                fileAction_ = "Modified";
                break;
            case 68:
                fileAction_ = "Deleted";
                break;
            default:
                qWarning() << "undifined index! Class revision_files: method dataInit: " + data;
            }
        }
            break;
        case FILE_NAME:
            fileName_ = data;
            break;
        default:
            qCritical() << "Error! Undifined behavior in method dataInit, class revision_files: " + data;
            //QMessageBox::critical(this, "Error", "Error! Undifined behavior in method dataInit, class revision_files: " + data);
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
