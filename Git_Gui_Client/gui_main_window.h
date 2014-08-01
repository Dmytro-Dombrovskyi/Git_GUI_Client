#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QDirModel>
#include <QTreeView>
#include "gitdata.h"
#include "my_data_model.h"

namespace Ui {
class Gui_Main_Window;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The Gui_Main_Window class
///
/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////
class Gui_Main_Window : public QMainWindow
{
    Q_OBJECT
public:
    explicit Gui_Main_Window(QWidget *parent = 0);
    ~Gui_Main_Window();
signals:

private slots:
    void on_actionExit_triggered ();
    void on_actionOpen_triggered ();
    void on_actionAbout_triggered();
    void mySlot() { }

protected:
    void                 set_programPath     (); // set default programm execution file(git.exe for windows or "git" for linux)
    bool                 set_workingDirectory();
    QString              get_workingDirectory() const {return workingDirectory_;}
    QString              start_process       (const QStringList & command); // start Git process and read output
    void                 start_programm      ();
    void                 update_TableView_1  ();
    QString              get_programPath     () const {return programPath_;}
    QVector<QStringList> processing_data     (const QString &data,
                         const QString splitter_1 = "\n",
                         const QString splitter_2 = "::");
private:
    Ui::Gui_Main_Window   * ui;
    QProcess              * Git;
    My_Data_Model         * mainModel;
    QSortFilterProxyModel * FilterForTable_Model_1;
    QItemSelectionModel   * SelectionModel;


    QString                 workingDirectory_;
    QString                 programPath_;
};

#endif // GUI_MAIN_WINDOW_H
