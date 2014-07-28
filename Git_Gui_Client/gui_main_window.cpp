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

}

Gui_Main_Window::~Gui_Main_Window()
{
    delete ui;
}

void Gui_Main_Window::on_actionExit_triggered()
{
    QApplication::instance()->quit();
}

void Gui_Main_Window::on_pushButton_Start_clicked()
{
//    QProcess Git;
//    Git.start("git");
//    Git.waitForReadyRead();
//    qDebug() << Git.readAll();
//    Git.write("git log");
//    qDebug() << Git.readAll();
//    Git.waitForFinished();

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
        hash_list << "log" << "--pretty=format:\"%h\"";

        Git->start(program_path, hash_list);
        Git->waitForFinished();

        QString data = Git->readAllStandardOutput();
        QString error = Git->readAllStandardError();

        if(!error.isEmpty())
          QMessageBox::warning(this, "Warning", error);

        QStringList hash;
        if(!data.isEmpty())
        {
            hash = data.split("\n");
            hash_model.setStringList(hash);
            ui->tableView->setModel(&hash_model);
        }
    }
}
