#include <Wt/WTable>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WContainerWidget>
#include <Wt/WLabel>
#include <Wt/WFileResource>
#include <Wt/WApplication>

#include "server/runners/simulationoutput.h"
#include "runresultsdialog.h"

using namespace Wt;
using namespace std;

RunResultDialog::RunResultDialog(const SimulationOutput& so):
    WDialog()
{
    so_ = so;
    setModal(true);
    WTable* t = new WTable(this->contents());
    int row = 0;
    
    WLabel* l = new WLabel(t->elementAt(row, 0));
    l->setText(tr("runresult.label.vmsclout"));
    
    ++row;
    WContainerWidget* c = new WContainerWidget(t->elementAt(row,0));
    c->resize(600, 270);
    c->setMargin(10);
    c->setOverflow(WContainerWidget::OverflowAuto);
    c->addWidget(new WText(WString::fromUTF8(so_.vmsCommandLineOutput()), PlainText));

    ++row;
    l = new WLabel(t->elementAt(row, 0));
    l->setText(tr("runresult.label.gmsclout"));

    ++row;
    c = new WContainerWidget(t->elementAt(row, 0));
    c->resize(600, 270);
    c->setMargin(10);
    c->setOverflow(WContainerWidget::OverflowAuto);
    c->addWidget(new WText(WString::fromUTF8(so_.gmsCommandLineOutput()), PlainText));

    ++row;
    WTable* buttonTable = new WTable(t->elementAt(row, 0));
    t->elementAt(row, 0)->setContentAlignment(AlignCenter);
    WPushButton* p = new WPushButton(tr("runresult.button.nodesinput"), buttonTable->elementAt(0, 0));
    p->resize(120, 30);
    p->clicked().connect(this, &RunResultDialog::nodesInputClicked);

    p = new WPushButton(tr("runresult.button.mobilityin"), buttonTable->elementAt(0, 1));
    p->resize(120, 30);
    p->clicked().connect(this, &RunResultDialog::mobilityInClicked);

    p = new WPushButton(tr("runresult.button.glomostat"), buttonTable->elementAt(0, 2));
    p->resize(120, 30);
    p->clicked().connect(this, &RunResultDialog::glomoStatClicked);

    resize(WLength(640), WLength(690));
    setTitleBarEnabled(true);
    setClosable(true);
    setWindowTitle(tr("runresult.title"));
}

void RunResultDialog::nodesInputClicked()
{
    downloadFile("nodes.input");
}

void RunResultDialog::downloadFile(const string& newFileName)
{
    WFileResource *fileResource = new Wt::WFileResource("text/plain", newFileName);
    fileResource->setDispositionType(Wt::WResource::Attachment);
    fileResource->suggestFileName(newFileName);

    WApplication::instance()->redirect(fileResource->url());
}

void RunResultDialog::mobilityInClicked()
{
    downloadFile("mobility.in");
}

void RunResultDialog::glomoStatClicked()
{
    downloadFile("glomo.stat");
}

