#include "gui_main_window.h"
#include "ui_gui_main_window.h"
#include <QProcess>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>


Gui_Main_Window::Gui_Main_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui_Main_Window)
{
    ui->setupUi(this);

    Git = new QProcess(this);
    my_item_model = new  QStandardItemModel(this);

    ui->textBrowser->setReadOnly(true);

    connect(ui->OpenButton, SIGNAL(clicked()), SLOT(on_actionOpen_triggered()) );
}

Gui_Main_Window::~Gui_Main_Window()
{
    delete ui;
}

void Gui_Main_Window::on_actionExit_triggered()
{
    QApplication::instance()->quit();
}

void Gui_Main_Window::on_actionOpen_triggered()
{
    if(set_workingDirectory())
    {
        start_programm();
    }
}

bool Gui_Main_Window::set_workingDirectory()
{
  QString DirectoryName =
          QFileDialog::getExistingDirectory(this,"Directory Path");
  if(DirectoryName.isEmpty()) return false;

  workingDirectory_ = DirectoryName;
  return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Gui_Main_Window::start_programm()
{
  if(!(get_workingDirectory().isEmpty()))
  {
      set_programPath(); // set default programm execution file(git.exe or "git")

      QStringList command;
      command << "log" << "--pretty=format:\"%h :: %an :: %ae :: %ce :: %cn :: %s :: %cd :: %cr\"";

      QString data = start_process(command); // start Git process and read output
      if(!data.isEmpty())
      {
          processing_data(data);
          set_myDataClass();
          set_myItemTableView_model_1();
          update_TableView_1();
      }
      command.clear();
      data.clear();

      data = start_process(QStringList() << "log" << "--pretty=format:" << "--name-status");
      if(!data.isEmpty())
        {
//          QStringList hash;
//          hash = data.split("\n\n");

//          qDebug() << hash;
          processing_data(data, "\n\n", "\n");
          set_revision_filesClass();
          set_myItemTableView_model_2();
          update_TableView_2();
        }
  }
}

void Gui_Main_Window::set_programPath()
{
  #ifdef Q_OS_WIN
    programPath_ = "C:\\Program Files (x86)\\Git\\bin\\git.exe";
  #else
    programPath_ = "git";
  #endif
}

QString Gui_Main_Window::start_process(const QStringList & command)
{
  Git->setWorkingDirectory(get_workingDirectory());
  Git->start(get_programPath(), command);
  Git->waitForFinished();
  QString error = Git->readAllStandardError();
  if(!error.isEmpty())
    {
      qDebug() << error;
    }
  return (Git->readAllStandardOutput());
}

void Gui_Main_Window::processing_data(const QString &data,
                                      const QString splitter_1,
                                      const QString splitter_2)
{
  QStringList hash;
  hash = data.split(splitter_1);

  foreach(QString hash_data, hash)
  {
      initialItemsForGitData_.append(QStringList() << hash_data.split(splitter_2));
  }
}

void Gui_Main_Window::set_myDataClass()
{
  foreach(QStringList data_temp, initialItemsForGitData_)
    {
        myData.append(new GitData(data_temp));
    }
}

void Gui_Main_Window::set_revision_filesClass()
{
  foreach(QStringList data_temp, initialItemsForGitData_)
    {
        updatingFiles.append(new revision_files(data_temp));
    }
}

void Gui_Main_Window::set_myItemTableView_model_2()
{
    for(int row = 0; row < updatingFiles.size(); ++row)
      {
        QStandardItem *item_fileName = new QStandardItem(updatingFiles.at(row)->get_fileName());
        QStandardItem *item_fileAction = new QStandardItem(updatingFiles.at(row)->get_fileAction());

        my_item_file_changes_model->setItem(row, 0, item_fileName);
        my_item_file_changes_model->setItem(row, 1, item_fileAction);
      }
    my_item_file_changes_model->setHorizontalHeaderLabels(QStringList()
                                                          << "File name"
                                                          << "Status");

}
void Gui_Main_Window::update_TableView_2()
{
  ui->tableView_Files->setModel(my_item_file_changes_model);
  ui->tableView_Files->resizeColumnsToContents();
  ui->tableView_Files->resizeRowsToContents();
}

void Gui_Main_Window::set_myItemTableView_model_1()
{
    for(int row = 0; row < myData.size(); ++row)
    {
        QStandardItem *item_datePeriod =
            new QStandardItem(myData.at(row)->get_datePeriod());
        QStandardItem *item_commiterEmail=
            new QStandardItem(myData.at(row)->get_commiter_Email());
        QStandardItem *item_message =
            new QStandardItem(myData.at(row)->get_commitMessage());

        my_item_model->setItem(row, 0, item_datePeriod);
        my_item_model->setItem(row, 1, item_commiterEmail);
        my_item_model->setItem(row, 2, item_message);
    }
    my_item_model->setHorizontalHeaderLabels(QStringList()
                                             << "Date"
                                             << "Commiter e-mail"
                                             << "Message");
}

void Gui_Main_Window::update_TableView_1()
{
  ui->tableView->setModel(my_item_model);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->resizeRowsToContents();
}

