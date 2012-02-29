
#include <string>

#include <Wt/WStandardItem>
#include <Wt/WSpinBox>
#include <Wt/WTable>
#include <Wt/WString>
#include <Wt/WLabel>

#include "vanetareapropertyform.h"

using namespace Wt;

VanetAreaPropertyForm::VanetAreaPropertyForm(WContainerWidget* parent): 
    WContainerWidget(parent), 
    fWidth(350), 
    fHeight(300),
    dimxLabel(tr("mappropertyeditor.group.general.dimx").toUTF8()),
    dimyLabel(tr("mappropertyeditor.group.general.dimy").toUTF8())
{
    WTable *formTable = new WTable(this);

    WLabel *xLabel = new WLabel(formTable->elementAt(0, 0));

    dimx = new WSpinBox(formTable->elementAt(0, 1));
}



