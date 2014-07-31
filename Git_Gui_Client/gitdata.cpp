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
  //file_changes_model = new QItemSelectionModel(this);
  //set_file_changes_model();
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
//    case 9:
//      filesAction_ = initialString;
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
//QString GitData::get_fileAction()const
//{
//  return filesAction_;
//}

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
//void GitData::set_filesAction_(QString fileAction)
//{
//  if(fileAction.isEmpty() || fileAction == filesAction_) return;
//  filesAction_ = fileAction;
//}

void GitData::set_file_changes_model()
{
    for(int row = 0; row < revisionFiles_.size(); ++row)
    {
        QStandardItem *item_FileName =
            new QStandardItem(revisionFiles_.at(row)->get_fileName());
        QStandardItem *item_message =
            new QStandardItem(revisionFiles_.at(row)->get_fileAction());

        file_changes_model->setItem(row, 0, item_FileName);
        file_changes_model->setItem(row, 1, item_message);
    }
    file_changes_model->setHorizontalHeaderLabels(QStringList()
                                             << "File name"
                                             << "Status");
}
