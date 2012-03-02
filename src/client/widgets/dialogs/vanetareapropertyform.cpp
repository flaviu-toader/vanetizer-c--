
#include <string>

#include <Wt/WStandardItem>
#include <Wt/WSpinBox>
#include <Wt/WTable>
#include <Wt/WString>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WBreak>

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
    int row = 0;

    formTable->elementAt(row, 0)->setColumnSpan(2);
    formTable->elementAt(row, 0)->setPadding(5);
    feedbackMessages = formTable->elementAt(row, 0);
    WCssDecorationStyle& errorStyle = feedbackMessages->decorationStyle();
    errorStyle.setForegroundColor(Wt::red);
    errorStyle.font().setSize(WFont::Smaller);
    errorStyle.font().setWeight(WFont::Bold);
    errorStyle.font().setStyle(WFont::Italic);

    ++row;
    WLabel *xLabel = new WLabel(formTable->elementAt(row, 0));
    xLabel->setText(fromUTF8(dimxLabel));
    dimx = new WSpinBox(formTable->elementAt(row, 1));
    dimx->setMinimum(0);
    dimx->setMaximum(2000);
    xLabel->setBuddy(dimx);

    ++row;
    WLabel *yLabel = new WLabel(formTable->elementAt(row, 0));
    yLabel->setText(fromUTF8(dimyLabel));
    dimy = new WSpinBox(formTable->elementAt(row, 1));
    dimy->setMinimum(0);
    dimy->setMaximum(2000);
    yLabel->setBuddy(dimy);

    ++row;
    formTable->elementAt(row, 0)->setColumnSpan(2);
    formTable->elementAt(row, 0)->setContentAlignment(AlignCenter);
    WPushButton *b;
    WContainerWidget *buttons = new WContainerWidget(formTable->elementAt(row, 0));
    buttons->addWidget(b = new WPushButton(tr("vanet.property.form.area.button.save")));
    b->clicked().connect(this, &WDialog::accept);
    contents()->enterPressed().connect(this, &WDialog::accept);
    buttons->addWidget(b = new WPushButton(tr("vanet.property.form.area.button.cancel")));
    b->clicked().connect(this, &WDialog::reject);

    finished().connect(this, &VanetAreaPropertyForm::submit);

    show();
}

WLength VanetAreaPropertyForm::formWidth() 
{
    return fWidth;
}

WLength VanetAreaPropertyForm::formHeight() 
{
    return fHeight;
}

bool VanetAreaPropertyForm::validate()
{
    feedbackMessages->clear();
    bool valid = true;
    if (dimx->value() < 100 || dimy->value() < 100) 
    {
        valid = false;
        feedbackMessages->addWidget(new WText(tr("vanet.property.form.area.error.dims")));
        feedbackMessages->addWidget(new WBreak());
    }
    return valid;
}

void VAnetAreaPropertyForm::submit(DialogCode result) 
{
    if (result == WDialog::Accepted && validate())
    {
    }
}
