#include "gui_main_window.h"
#include "ui_gui_main_window.h"

#include <QProcess>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>

// constructor
Gui_Main_Window::Gui_Main_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui_Main_Window)
{
    ui->setupUi(this);
    Git = new QProcess(this); 
    ui->textBrowser->setReadOnly(true);
    connect(ui->OpenButton, SIGNAL(clicked()), SLOT(on_actionOpen_triggered()) );
}

Gui_Main_Window::~Gui_Main_Window()
{
    Git->close();
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
      set_programPath(); // set default programm execution file(git.exe for windows or "git" for linux)

      QStringList command;
      command << "log" << "--pretty=format:\"%h :: %an :: %ae :: %ce :: %cn :: %s :: %cd :: %cr\"";

      QString data1 = start_process(command); // start Git process and read output
      command.clear();

      command << "log" << "--pretty=format:" << "--name-status";
      QString data2 = start_process(command);

      if(!data1.isEmpty())
      {
         QVector<QStringList> initialItemsForGitData = processing_data(data1);

          set_myDataClass(initialItemsForGitData);         
          update_TableView_1();
      }
      command.clear();
      data1.clear();

      if(!data2.isEmpty())
        {
           QStringList temp = data2.split("\n\n");
           int count =  0;
           foreach(QString doubleString, temp)
             {
               myData.at(count)->set_revisionFiles(doubleString);
             }
        }
      data2.clear();      
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

QVector<QStringList> Gui_Main_Window::processing_data(const QString &data,
                                      const QString splitter_1,
                                      const QString splitter_2)
{
  QStringList hash;
  hash = data.split(splitter_1);

  QVector<QStringList> datalist;
  foreach(QString hash_data, hash)
  {
      datalist.append(QStringList() << hash_data.split(splitter_2));
  }
  return datalist;
}

void Gui_Main_Window::set_myDataClass(const QVector<QStringList> &data)
{
  for(int i = 0; i < data.size(); ++i)
    {
        myData.append(new GitData(data.at(i)));
    }
}

// set my model with data to table view 1.
void Gui_Main_Window::update_TableView_1()
{
  mainModel = new My_Data_Model(myData, this);

  ui->tableView->setModel(mainModel);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->resizeRowsToContents();
}
