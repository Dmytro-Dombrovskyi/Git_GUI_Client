#ifndef BROWSERWITHCHANGES_H
#define BROWSERWITHCHANGES_H

#include <QDialog>

namespace Ui {
class BrowserWithChanges;
}

class BrowserWithChanges : public QDialog
{
    Q_OBJECT

public:
    explicit BrowserWithChanges(QWidget *parent = 0);
    ~BrowserWithChanges();

private:
    Ui::BrowserWithChanges *browserUi;


public slots:

signals:
    void setBrowserChangesText(const QString &);

};

#endif // BROWSERWITHCHANGES_H
