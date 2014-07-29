#ifndef GITDATA_H
#define GITDATA_H

#include <QtGui>
#include <QtCore>

struct revision_files;

class GitData
{
public:

    GitData(QString hash,
             QString autorName = "",
             QString autorEmail = "",
             QString commiterEmail = "",
             QString commiterName = "",
             QString commitMessage = "",
             QString date = "",
             QString datePeriod = "");
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

    //QVector<revision_files> get_revisionFiles()const;

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

    void GitDataInit(const unsigned int number, const QString &initialString);
    //void set_revisionFiles();
private:
    QString hash_;

    QString autorName_;
    QString autorEmail_;

    QString commiterEmail_;
    QString commiterName_;
    QString commitMessage_;

    QString date_;
    QString datePeriod_;

};

struct revision_files
{
    QString file_path_;
    QString file_status_;
    QString file_lines_added_;
    QString file_lines_removed_;
};
#endif // GITDATA_H
