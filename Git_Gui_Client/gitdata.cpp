#include "gitdata.h"

// constructor
GitData::GitData(const QStringList &initialData)
{
  if(!(initialData.isEmpty()))
    {
      unsigned int counter = 1;
      foreach(QString initialItem, initialData)
        {
          if(!(initialItem.isEmpty()))
              GitDataInit(counter, initialItem);
          ++counter;
        }
    }  
}

// Data initialize
void GitData::GitDataInit(const unsigned int number, const QString &initialString)
{
  switch(number)
    {
    case 1:
      hash_ = initialString;
    break;
    case 2:
      autorName_ = initialString;
    break;
    case 3:
      autorEmail_ = initialString;
    break;
    case 4:
      commiterEmail_ = initialString;
    break;
    case 5:
      commiterName_ = initialString;
    break;
    case 6:
      commitMessage_ = initialString;
    break;
    case 7:
      date_ = initialString;
    break;
    case 8:
      datePeriod_ = initialString;
    break;
  default:
    qDebug() << "Initial error";
    return;
    }
}
void GitData::set_revisionFiles(QString files)
{
    QStringList strings = files.split("\n");
    foreach(QString current, strings)
      {
        revisionFiles_.append(new revision_files(current));
      }
}

//////////////////////////////////////////////////////////////////////////

// set methods
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
//////////////////////////////////////////////////////////////////////////////
