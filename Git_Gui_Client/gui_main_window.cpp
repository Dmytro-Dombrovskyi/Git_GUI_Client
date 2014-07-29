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

    QStringList data_header;
    data_header << "Date" << "Commiter e-mail" << "Message";
    my_item_model->setHorizontalHeaderLabels(data_header);

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
    QString DirectoryName =
            QFileDialog::getExistingDirectory(this,"Directory Path");
    if(!DirectoryName.isEmpty())
    {
        Git->setWorkingDirectory(DirectoryName);
        QString program_path;

    #ifdef Q_OS_WIN
        program_path = "C:\\Program Files (x86)\\Git\\bin\\git.exe";
        //Git->setProgram("C:\\Program Files (x86)\\Git\\bin\\git.exe");
    #else
        program_path = "git";
        //Git->setProgram("git");
    #endif

        QStringList hash_list;
        hash_list << "log" << "--pretty=format:\"%h :: %an :: %ae :: %ce :: %cn :: %s :: %cd :: %ci\"";

        Git->start(program_path, hash_list);
        Git->waitForFinished();

        QString data = Git->readAllStandardOutput();
        QString error = Git->readAllStandardError();
        hash_list.clear();

        if(!error.isEmpty())
          qDebug() << error;
          //QMessageBox::warning(this, "Warning", error);
//
        if(!data.isEmpty())
        {
            QStringList hash;
            QStringList message_from_hash;

            hash = data.split("\n");

//            QVector<QStringList> initialItemsForGitData;
//            foreach(QString current_string, initialData)
//              {
//                initialItemsForGitData.append(QStringList(current_string.split("::"));
//              }




           //QVector<QStringList> message_data;
            QVector<QStringList> initialItemsForGitData;


            foreach(QString hash_data, hash)
              {
          //      message_from_hash = hash_data.split("::");
          //      message_data.append(message_from_hash);
           //     message_from_hash.clear();
                //message_data.append(QStringList() << hash_data.split("::"));
                initialItemsForGitData.append(QStringList() << hash_data.split("::"));
              }
            //myData.resize(initialItemsForGitData.size());
            foreach(QStringList data_temp, initialItemsForGitData)
              {
                  myData.append(new GitData(data_temp));
              }

//           unsigned int column_num = 0;
//           foreach(QStringList data_temp, message_data)
//           {
//               unsigned int row_num = 0;
//               foreach(QString temp_string, data_temp)
//                 {
//                   QStandardItem *item = new QStandardItem(temp_string);
//                   my_item_model->setItem(column_num, row_num, item);
//                   row_num++;
//                 }
//                column_num++;
//           }
          for(int row = 0; row < myData.size(); ++row)
            {
              //int col = 0;
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

          ui->tableView->setModel(my_item_model);
          ui->tableView->resizeColumnsToContents();
          ui->tableView->resizeRowsToContents();

        }
    }
}
