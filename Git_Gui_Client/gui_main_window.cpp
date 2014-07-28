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
    data_header << "Date" << "Commiter e-mail" << "Message" << "Hash";
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

        QStringList hash_list; // = "log --pretty=format:\"%h\"";
        hash_list << "log" << "--pretty=format:\"%ar :: %ce :: %s :: %h\"";

        Git->start(program_path, hash_list);
        Git->waitForFinished();

        QString data = Git->readAllStandardOutput();
        QString error = Git->readAllStandardError();
        hash_list.clear();

        if(!error.isEmpty())
          QMessageBox::warning(this, "Warning", error);

//        QStringList autor_name_from_hash;
//        QStringList data_from_hash;

        if(!data.isEmpty())
        {
            QStringList hash;
            QStringList message_from_hash;

            hash = data.split("\n");
            QVector<QStringList> message_data;

            foreach(QString hash_data, hash)
            {
                message_from_hash = hash_data.split("::");
                message_data.append(message_from_hash);
                message_from_hash.clear();
            }

           unsigned int column_num = 0;
           foreach(QStringList data_temp, message_data)
           {
               unsigned int row_num = 0;
               foreach(QString temp_string, data_temp)
                 {
                   QStandardItem *item = new QStandardItem(temp_string);
                   my_item_model->setItem(column_num, row_num, item);
                   row_num++;
                 }
                column_num++;
           }

          ui->tableView->setModel(my_item_model);
          ui->tableView->resizeColumnsToContents();
          ui->tableView->resizeRowsToContents();

        }
    }
}
