#ifndef GITDATA_H
#define GITDATA_H

#include <QtGui>
#include <QtCore>

struct revision_files;
// class store data
class GitData
{
public:
    explicit GitData(const QStringList &initialData);
    virtual ~GitData() {}
    QString get_hash()const;
    QString get_autorName()const;
    QString get_autorEmail()const;
    QString get_commiter_Email()const;
    QString get_commiterName()const;
    QString get_commitMessage()const;
    QString get_date()const;
    QString get_datePeriod()const;
//    QString get_fileAction()const;

    //QVector<revision_files> get_revisionFiles()const;
    void set_revisionFiles(QString files);


    QVector<revision_files*> revisionFiles_;

    QStandardItemModel *file_changes_model;
protected:
    //QVector<revision_files> revisionFiles_;


    void set_hash(QString hash);
    void set_autorName(QString autorName);
    void set_autorEmail(QString autorEmail);
    void set_commiterEmail(QString commiterEmail);
    void set_commiterName(QString commiterName);
    void set_commitMessage(QString commitMessage);
    void set_date(QString date);
    void set_datePeriod(QString datePeriod);
//    void set_filesAction_(QString fileAction);

    void GitDataInit(const unsigned int number, const QString &initialString);
    void set_file_changes_model();
private:
    QString hash_;
    QString autorName_;
    QString autorEmail_;
    QString commiterEmail_;
    QString commiterName_;
    QString commitMessage_;
    QString date_;
    QString datePeriod_;


//    QString filesAction_;
};


// class which contain data in Format: File - Action
class revision_files
{
private:
    QString fileAction_;
    QString fileName_;
protected:

public:
    revision_files(QString line)
    {
      QStringList items = line.split("\t");
      if(items.size() == 2)
        {
          fileAction_ = items.at(0);
          fileName_ = items.at(1);
        }
    }

    virtual ~revision_files() {}

    QString get_fileAction()const  {return fileAction_;}
    QString get_fileName()const    {return fileName_;}
};

#endif // GITDATA_H
