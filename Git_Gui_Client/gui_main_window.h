#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QDirModel>
#include <QTreeView>


namespace Ui {
class Gui_Main_Window;
}

class Gui_Main_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui_Main_Window(QWidget *parent = 0);
    ~Gui_Main_Window();

private slots:    

    void on_actionExit_triggered();

    void on_pushButton_Start_clicked();

    void on_actionOpen_triggered();

private:
    Ui::Gui_Main_Window *ui;
    QProcess *Git;

};

#endif // GUI_MAIN_WINDOW_H
