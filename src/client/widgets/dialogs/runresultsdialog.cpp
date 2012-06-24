#include <Wt/WTable>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WContainerWidget>
#include <Wt/WLabel>

#include "server/runners/simulationoutput.h"
#include "runresultsdialog.h"

using namespace Wt;
using namespace std;

RunResultDialog::RunResultDialog(const SimulationOutput& so):
    WDialog()
{
    so_ = so;
    resize(WLength(660), WLength(800));
    setModal(true);
    WTable* t = new WTable(this->contents());
    int row = 0;
    
    WLabel* l = new WLabel(t->elementAt(row, 0));
    l->setText(tr("runresult.label.vmsclout"));
    
    ++row;
    WContainerWidget* c = new WContainerWidget(t->elementAt(row,0));
    c->addWidget(new WText(WString::fromUTF8(so_.vmsCommandLineOutput()), PlainText));

    ++row;
    l = new WLabel(t->elementAt(row, 0));
    l->setText(tr("runresult.label.gmclout"));

    ++row;
    c = new WContainerWidget(t->elementAt(row, 0));
    c->addWidget(new WText(WString::fromUTF8(so_.gmsCommandLineOutput()), PlainText));

    ++row;
    WTable* buttonTable = new WTable(t->elementAt(row, 0));
    WPushButton* p = new WPushButton(tr("runresult.button.nodesinput"), buttonTable->elementAt(0, 0));
    p->resize(120, 30);
    p->clicked().connect(this, &RunResultDialog::nodesInputClicked);

    p = new WPushButton(tr("runresult.button.mobilityin"), buttonTable->elementAt(0, 1));
    p->resize(120, 30);
    p->clicked().connect(this, &RunResultDialog::mobilityInClicked);

    p = new WPushButton(tr("runresult.button.glomostat"), buttonTable->elementAt(0, 2));
    p->resize(120, 30);
    p->clicked().connect(this, &RunResultDialog::glomoStatClicked);
}

void RunResultDialog::nodesInputClicked()
{
}

void RunResultDialog::mobilityInClicked()
{
}

void RunResultDialog::glomoStatClicked()
{
}

