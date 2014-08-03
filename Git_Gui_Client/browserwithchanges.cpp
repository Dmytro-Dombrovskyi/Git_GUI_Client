#include "browserwithchanges.h"
#include "ui_browserwithchanges.h"

BrowserWithChanges::BrowserWithChanges(QWidget *parent) :
    QDialog(parent),
    browserUi(new Ui::BrowserWithChanges)
{
    browserUi->setupUi(this);

    connect(this, SIGNAL(setBrowserChangesText(QString)), browserUi->textBrowser_Changes, SLOT(setText(QString)));
}

BrowserWithChanges::~BrowserWithChanges()
{
    delete browserUi;
}
