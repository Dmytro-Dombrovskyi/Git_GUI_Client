#ifndef GUI_MAIN_WINDOW_H
#define GUI_MAIN_WINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QMessageBox>
#include <QDirModel>
#include <QTreeView>

#include "gitdata.h"
#include "my_data_model.h"
#include "seconddatamodel.h"
#include "browserwithchanges.h"
#include "ui_browserwithchanges.h"


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
    void DeleteSecondModel();

signals:
    void setDataFromIndex(const QString &);
    void setDataInTable2(const QModelIndex &);

private slots:
    void on_actionExit_triggered ();
    void on_actionOpen_triggered ();
    void on_actionAbout_triggered();

    void on_pushButton_Statistic_clicked();

public slots:
    void catchDataIndex  (const QModelIndex &);
    void setNewModelFiles(const QModelIndex &);

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
    Ui::Gui_Main_Window    *  ui;
    QProcess               *  Git;
    My_Data_Model          *  mainModel;
    QVector<SecondDataModel*> secondModel;
    QSortFilterProxyModel  *  FilterForTable_Model_1;

///    QItemSelectionModel   * SelectionModel;
///    QMessageBox           * StatisticBox;

    QString                 workingDirectory_;
    QString                 programPath_;

    BrowserWithChanges     * browserChanges_;
};

#endif // GUI_MAIN_WINDOW_H

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
