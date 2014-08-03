#include "gui_main_window.h"
#include "ui_gui_main_window.h"

#include <QProcess>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDesktopServices>
#include <QUrl>
#include <QWindow>


/////////////////////////////////////////////////////////////////////////////////////////////
/// constructor
/// set ui
/// set Process
/// set connection
/// set colors
////////////////////////////////////////////////////////////////////////////////////////////
Gui_Main_Window::Gui_Main_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui_Main_Window)
{
    ui->setupUi(this);    
    ui->lineEdit_FilterPeriod->setFixedWidth(150);
    ui->textBrowser->setReadOnly(true);

    Git = new QProcess(this);
    FilterForTable_Model_1 = new QSortFilterProxyModel;



    QPalette pal = ui->ExitButton->palette();
    pal.setBrush(QPalette::Button, QBrush(Qt::white, Qt::Dense3Pattern));
    pal.setColor(QPalette::ButtonText, Qt::blue);
    pal.setColor(QPalette::Text, Qt::white);
    pal.setColor(QPalette::Active, QPalette::Base, Qt::black);

    ui->ExitButton->setPalette(pal);
    ui->OpenButton->setPalette(pal);
    ui->centralwidget->setPalette(pal);

    this->setPalette(pal);

    connect(ui->tableView, SIGNAL(clicked(QModelIndex)),this, SLOT(catchDataIndex(QModelIndex)) );
    connect(ui->tableView, SIGNAL(activated(QModelIndex)),this, SLOT(catchDataIndex(QModelIndex)) );
    connect(this, SIGNAL(setDataFromIndex(QString)), ui->textBrowser, SLOT(setText(QString)) );
    connect(ui->OpenButton, SIGNAL(clicked()), SLOT(on_actionOpen_triggered()) );
    connect(ui->lineEdit_FilterPeriod, SIGNAL(textChanged(QString)), FilterForTable_Model_1, SLOT(setFilterWildcard(QString)) );
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(setNewModelFiles(QModelIndex)));

}

//////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Gui_Main_Window::~Gui_Main_Window
/// Destructor:
/// Close QProcess
/// delete memory
//////////////////////////////////////////////////////////////////////////////////////////////
Gui_Main_Window::~Gui_Main_Window()
{
    Git->close();
    delete ui;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Gui_Main_Window::on_actionExit_triggered
/// Action Quit: Quit programm
//////////////////////////////////////////////////////////////////////////////////////////////
void Gui_Main_Window::on_actionExit_triggered()
{
    QApplication::instance()->quit();
}

/////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Gui_Main_Window::on_actionOpen_triggered
/// Action Open: get dialog for user///
/// If this folder exist - start program
////////////////////////////////////////////////////////////////////////////////////////////
void Gui_Main_Window::on_actionOpen_triggered()
{
    if(set_workingDirectory())
    {
        start_programm();
    }    
}

////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Gui_Main_Window::set_workingDirectory
///  Dialog for user:
/// User should pen .git folder or folder which have .git folder
/// If this folder exist - set working derectory and
/// return true if operation was ok or false otherwise
//////////////////////////////////////////////////////////////////////////////////////////////
bool Gui_Main_Window::set_workingDirectory()
{
  QString DirectoryName =
          QFileDialog::getExistingDirectory(this,"Directory Path");
  if(DirectoryName.isEmpty()) return false;

  workingDirectory_ = DirectoryName;

  ui->statusbar->showMessage("Load from: \t" + DirectoryName); // set status bar
  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Gui_Main_Window::start_programm
///  Set default programm execution file(git.exe for windows or "git" for linux),
///  Start QProcess with parametrs:
///  Processing data ouput
///  Set my TableModel
///  Set TableViews
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Gui_Main_Window::start_programm()
{
  if(!(get_workingDirectory().isEmpty()))
  {
      set_programPath(); // set default programm execution file(git.exe for windows or "git" for linux)

      QStringList command; // command for git
      command << "log" << "--pretty=format:\"%H :: %an :: %ae :: %ce :: %cn :: %s :: %cd :: %cr\"";

      QString data1 = start_process(command); // start Git process and read output
      command.clear();

      command << "log" << "--pretty=format:" << "--name-status";
      QString data2 = start_process(command);

      if(!data1.isEmpty() && !data2.isEmpty())
        {
          QVector<QStringList> initialItemsForGitData_1 = processing_data(data1);
          QStringList initialItemsForGitData_2 = data2.split("\n\n");

          mainModel = new My_Data_Model(initialItemsForGitData_1, this);

          QStringList initDataForSeconModel;
          foreach(QString dataList, initialItemsForGitData_2)
          {
              initDataForSeconModel = dataList.split("\n");
              secondModel.append(new SecondDataModel(initDataForSeconModel, this));
              initDataForSeconModel.clear();
          }
          update_TableView_1();
        }
    }
}

//////////////////////////////////////////////////////////////////////////
/// \brief Gui_Main_Window::set_programPath
/// set program execution file depends platform
/////////////////////////////////////////////////////////////////////////
void Gui_Main_Window::set_programPath()
{
  #ifdef Q_OS_WIN
    programPath_ = "C:\\Program Files (x86)\\Git\\bin\\git.exe";
  #else
    programPath_ = "git";
  #endif
}

/////////////////////////////////////////////////////////////////////////
/// Start QProcess, set program and run command.
/// Return data output if process run correctly,
/// else get error message
/// /////////////////////////////////////////////////////////////////////
QString Gui_Main_Window::start_process(const QStringList & command)
{
  Git->setWorkingDirectory(get_workingDirectory());
  Git->start(get_programPath(), command);
  Git->waitForFinished();
  QString error = Git->readAllStandardError();
  if(!error.isEmpty())
    {
      qDebug() << error;
      QMessageBox::critical(this,"Error", error);
    }
  return (Git->readAllStandardOutput());
}

////////////////////////////////////////////////////////////////////////////
/// Divede data from string(Data output from Git returned process)
/// Processing data and prepare for my own QTableModel
////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////
/// Set my tableModel class to TableView1,
/// than set correct size for rows and coulmns
////////////////////////////////////////////////////////////////////////////////
void Gui_Main_Window::update_TableView_1()
{  
  // set filter and connect to model

  FilterForTable_Model_1->setSourceModel(mainModel);
  FilterForTable_Model_1->setFilterCaseSensitivity(Qt::CaseInsensitive);
  FilterForTable_Model_1->setFilterKeyColumn(6);

  // set table View 1
  ui->tableView->setModel(FilterForTable_Model_1);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->resizeRowsToContents();
  ui->tableView->setVisible(true);

  // hide columns in table View 1
  ui->tableView->setColumnHidden(0, true);
  ui->tableView->setColumnHidden(1, true);
  ui->tableView->setColumnHidden(2, true);
  ui->tableView->setColumnHidden(5, true);
  ui->tableView->setColumnHidden(7, true);
}

/////////////////////////////////////////////////////////////////////////////////
/// Set Help message: add links for my Github with source,
/// add link on git website
/// ////////////////////////////////////////////////////////////////////////////
// help message
void Gui_Main_Window::on_actionAbout_triggered()
{
    QMessageBox aboutBox;
    aboutBox.setIcon(QMessageBox::Information);
    aboutBox.setWindowTitle("Information");
    aboutBox.setText(tr("Gui Client for git."));

    aboutBox.setInformativeText(tr("You can load source from:  "
                                  "<a href='https://github.com/Dmytro-Dombrovskyi/Git_GUI_Client'>Git_GUI_Client</a> "
                                   "Author e-mail: dombrovskiy11@gmail.com \n"
                                   "More about Git: "
                                   "<a href='http://git-scm.com/'>git-scm.com</a>"));

    aboutBox.setSizePolicy( QSizePolicy(QSizePolicy::Preferred,
    QSizePolicy::Preferred));
    aboutBox.setSizeGripEnabled(true);
    aboutBox.setAttribute(Qt::WA_Resized);
    aboutBox.setStandardButtons(QMessageBox::Close);
    aboutBox.exec();
}

// Slot for setting text
void Gui_Main_Window::catchDataIndex(const QModelIndex & index)
{
    if(index.isValid())
    {
        QString SHA_1 =      "<H4> SHA-1: <font color=\"#FF8798\"> " +
                             mainModel->myDataItem_.at(index.row())->get_hash().toHtmlEscaped() +
                             "</font></H4>";

        QString commit =     "<H3> Commit: <b><font color=\"#F79105\"> *" +
                             mainModel->myDataItem_.at(index.row())->get_commitMessage() +
                             "</font></b></H3>";

        QString commiter =   "<H4> Commiter: <i><font color=\"#E0E0EB\"> " +
                             mainModel->myDataItem_.at(index.row())->get_commiterName() +
                             "\"" + mainModel->myDataItem_.at(index.row())->get_commiter_Email() + "\"" +
                             "</font></i></H4>";

        QString autor  =     "<H4> Autor: <i><font color=\"#E0E0EB\"> " +
                             mainModel->myDataItem_.at(index.row())->get_autorName() +
                             " \" " + mainModel->myDataItem_.at(index.row())->get_autorEmail() + " \" " +
                             "</font></i></H4>";

        emit setDataFromIndex(SHA_1 + commit + commiter + autor);
    }
}

void Gui_Main_Window::setNewModelFiles(const QModelIndex & index)
{
    if(index.isValid())
    {
        // set Table View 2
        ui->tableView_Files->setModel(secondModel.at(index.row()));
        ui->tableView_Files->resizeColumnToContents(0);
        ui->tableView_Files->resizeRowsToContents();
    }
}
