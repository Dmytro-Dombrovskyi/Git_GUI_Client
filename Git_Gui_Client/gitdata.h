#ifndef GITDATA_H
#define GITDATA_H

#include <QtGui>
#include <QtCore>

struct revision_files;

class GitData
{
public:

    GitData( QString hash, QString autorName,
             QString autorEmail, QString commiterEmail,
             QString commitMessage, QString date,
             QString datePeriod);

    virtual ~GitData() {}
    QString get_hash()const;
    QString get_autorName()const;
    QString get_autorEmail()const;
    QString get_commiter_Email()const;
    QString get_commitMessage()const;
    QString get_date()const;
    QString get_datePeriod()const;

    QVector<revision_files> get_revisionFiles()const;

protected:
    QVector<revision_files> revisionFiles_;

    void set_hash();
    void set_autorName();
    void set_autorEmail();
    void set_commiterEmail();
    void set_commitMessage();
    void set_date();
    void set_datePeriod();

    void set_revisionFiles();
private:
    QString hash_;

    QString autorName_;
    QString autorEmail_;

    QString commiter_Email_;

    QString commitMessage_;

    QString date_;
    QString datePeriod_;

    QVector<revision_files> revisionFiles_;

};

struct revision_files
{
    QString file_path_;
    QString file_status_;
    QString file_lines_added_;
    QString file_lines_removed_;
};
#endif // GITDATA_H
