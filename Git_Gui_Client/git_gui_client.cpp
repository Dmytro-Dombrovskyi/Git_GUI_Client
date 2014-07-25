#include "git_gui_client.h"
#include "ui_git_gui_client.h"

Git_Gui_Client::Git_Gui_Client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Git_Gui_Client)
{
    ui->setupUi(this);
}

Git_Gui_Client::~Git_Gui_Client()
{
    delete ui;
}
