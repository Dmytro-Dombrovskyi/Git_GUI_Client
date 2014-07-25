#ifndef GIT_GUI_CLIENT_H
#define GIT_GUI_CLIENT_H

#include <QDialog>

namespace Ui {
class Git_Gui_Client;
}

class Git_Gui_Client : public QDialog
{
    Q_OBJECT

public:
    explicit Git_Gui_Client(QWidget *parent = 0);
    ~Git_Gui_Client();

private:
    Ui::Git_Gui_Client *ui;
};

#endif // GIT_GUI_CLIENT_H
