#include "git_gui_client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Git_Gui_Client w;
    w.show();

    return a.exec();
}
