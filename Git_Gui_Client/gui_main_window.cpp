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
    QProcess Git;
    Git.start("git");
    Git.waitForReadyRead();
    qDebug() << Git.readAll();
    Git.write("git log");
    qDebug() << Git.readAll();
    Git.waitForFinished();

}

void Gui_Main_Window::on_actionOpen_triggered()
{
    QString DirectoryName =
            QFileDialog::getExistingDirectory(this,"Directory Path");
    if(!DirectoryName.isEmpty())
    {
        Git->setWorkingDirectory(DirectoryName);
        QStringList arguments;
        Git->start("git",arguments);
        if(Git->waitForStarted()) return;

        QString message = Git->readAllStandardOutput();
        QString error_message = Git->readAllStandardError();

        if(!error_message.isEmpty())
            QMessageBox::warning(this, "Warning", error_message);
        if(!message.isEmpty())
            ui->listWidget->insertItems(message.size(), message);

    }

}
