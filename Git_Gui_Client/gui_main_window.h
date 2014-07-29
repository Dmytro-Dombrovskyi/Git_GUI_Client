#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QDirModel>
#include <QTreeView>
#include "gitdata.h"

namespace Ui {
class Gui_Main_Window;
}

class Gui_Main_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui_Main_Window(QWidget *parent = 0);
    ~Gui_Main_Window();
signals:


private slots:
    void on_actionExit_triggered();

    void on_actionOpen_triggered();

//    void textBrowser_update(int position);

private:
    Ui::Gui_Main_Window *ui;
    QProcess *Git;
    QStringListModel hash_model;

    QVector<GitData*> myData;

    QStandardItemModel *my_item_model;

    QStandardItemModel *my_text_model;

    QStandardItem *parentItem;
};

#endif // GUI_MAIN_WINDOW_H
