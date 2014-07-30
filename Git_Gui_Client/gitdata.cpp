#include "gitdata.h"
//hash_list << "log" << "--pretty=format:\"%h :: %an :: %ae :: %ce :: %cn :: %s :: %cd :: %cr\"";
GitData::GitData(QString hash,
                 QString autorName,
                 QString autorEmail,
                 QString commiterEmail,
                 QString commiterName,
                 QString commitMessage,
                 QString date,
                 QString datePeriod) :
    hash_(hash), //1
    autorName_(autorName), //2
    autorEmail_(autorEmail), //3
    commiterEmail_(commiterEmail), //4
    commiterName_(commiterName), //5
    commitMessage_(commitMessage), //6
    date_(date), //7
    datePeriod_(datePeriod) //8
{

}
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

revision_files::revision_files(const QStringList &initData)
{
  if(!(initData.isEmpty()))
    {
      unsigned int counter = 1;
      foreach (QString initialItem, initData )
        {
          if(!(initialItem.isEmpty()))
            {
              dataInit(counter, initialItem);
            }
          ++counter;
        }
    }
}

void revision_files::dataInit(const unsigned int number, const QString &initString)
{
  switch(number)
    {
    case 1:
      fileAction_ = initString;
      break;
    case 2:
      fileName_ = initString;
      break;
    default:
      qDebug() << "Fail Data init!";
    }
}

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

// get methods
// todo : ask if I should return const QString instead QString!

QString GitData::get_hash()const
{
    return hash_;
}
QString GitData::get_autorName()const
{
    return autorName_;
}
QString GitData::get_autorEmail()const
{
    return autorEmail_;
}
QString GitData::get_commiter_Email()const
{
    return commiterEmail_;
}
QString GitData::get_commiterName()const
{
    return commiterName_;
}
QString GitData::get_commitMessage()const
{
    return commitMessage_;
}
QString GitData::get_date()const
{
    return date_;
}
QString GitData::get_datePeriod()const
{
    return datePeriod_;
}

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
