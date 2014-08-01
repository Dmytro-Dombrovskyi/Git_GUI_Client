#include "gui_main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gui_Main_Window w;
    w.show();

    return a.exec();
}
