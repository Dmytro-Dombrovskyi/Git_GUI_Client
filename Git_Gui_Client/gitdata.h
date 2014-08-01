#ifndef GITDATA_H
#define GITDATA_H

#include <QtGui>
#include <QtCore>

struct revision_files; // forward decl.

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The GitData class
///  Class stored data from QProcess output (Database class)
/// /////////////////////////////////////////////////////////////////////////////////////////////////
class GitData
{
public:
    explicit GitData(const QStringList &initialData);
    virtual ~GitData();

    QString get_hash()          const {return hash_;}
    QString get_autorName()     const {return autorName_;}
    QString get_autorEmail()    const {return autorEmail_;}
    QString get_commiter_Email()const {return commiterEmail_;}
    QString get_commiterName()  const {return commiterName_;}
    QString get_commitMessage() const {return commitMessage_;}
    QString get_date()          const {return date_;}
    QString get_datePeriod()    const {return datePeriod_;}
    int get_size()              const {return SIZE;}

    //QVector<revision_files> get_revisionFiles()const;
    void set_revisionFiles(QString files);

    QVector<revision_files*> revisionFiles_;

protected:
    // set data methods
    void set_hash           (QString hash);
    void set_autorName      (QString autorName);
    void set_autorEmail     (QString autorEmail);
    void set_commiterEmail  (QString commiterEmail);
    void set_commiterName   (QString commiterName);
    void set_commitMessage  (QString commitMessage);
    void set_date           (QString date);
    void set_datePeriod     (QString datePeriod);

    void GitDataInit(const unsigned int number,
                     const QString &initialString);
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

      enum {AUTOR_EMAIL,
            AUTOR_NAME,
            COMMITER_NAME,
            COMMITER_EMAIL,
            COMMIT,
            DATE,
            DATE_PERIOD,
            HASH,
            SIZE
           };
};

///////////////////////////////////////////////////////////////////////////////////////
///
/// class which contain data in Format: File - Action
///
/// ///////////////////////////////////////////////////////////////////////////////////
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
    QString get_fileName  ()const  {return fileName_;}
};

#endif // GITDATA_H
