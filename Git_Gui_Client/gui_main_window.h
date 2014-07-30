#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QDirModel>
#include <QTreeView>
#include "gitdata.h"

namespace Ui {
class Gui_Main_Window;
}

class Gui_Main_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui_Main_Window(QWidget *parent = 0);
    ~Gui_Main_Window();
signals:

private slots:
    void on_actionExit_triggered();

    void on_actionOpen_triggered();

//    void textBrowser_update(int position);
protected:
    QString load_data();
    bool set_workingDirectory();
    QString get_workingDirectory() const {return workingDirectory_;}
    QString start_process(const QStringList & command);
    void set_programPath();
    QString get_programPath() const {return programPath_;}
    void processing_data(const QString &data,
                         const QString splitter_1 = "\n",
                         const QString splitter_2 = "::");
    void set_myDataClass();
    void set_myItemTableView_model_1();
    void update_TableView_1();
    void start_programm();

    void set_revision_filesClass();
    void set_myItemTableView_model_2();
    void update_TableView_2();
private:
    Ui::Gui_Main_Window *ui;
    QProcess *Git;
    QStringListModel hash_model;

    QVector<GitData*> myData;
    QVector<revision_files*> updatingFiles;

    QStandardItemModel *my_item_model;
    QStandardItemModel *my_item_file_changes_model;

    QStandardItemModel *my_text_model;
    QStandardItem *parentItem;

    QString workingDirectory_;
    QString programPath_;
    QVector<QStringList> initialItemsForGitData_;

};

#endif // GUI_MAIN_WINDOW_H
