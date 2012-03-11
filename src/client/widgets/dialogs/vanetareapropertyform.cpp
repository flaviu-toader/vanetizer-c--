
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

#include <Wt/WStandardItem>
#include <Wt/WSpinBox>
#include <Wt/WTable>
#include <Wt/WString>
#include <Wt/WLabel>
#include <Wt/WStandardItemModel>

#include "logger.h"
#include "vanetareapropertyform.h"
#include "client/widgets/dialogs/abstractpropertyform.h"

using namespace Wt;

VanetAreaPropertyForm::VanetAreaPropertyForm(WStandardItemModel *model, WContainerWidget* parent): 
    model_(model),
    dimxLabel_(tr("mappropertyeditor.group.general.dimx").toUTF8()),
    dimyLabel_(tr("mappropertyeditor.group.general.dimy").toUTF8())
{
    WTable *formTable = new WTable(this);
    int row = 0;

    WLabel *xLabel = new WLabel(formTable->elementAt(row, 0));
    xLabel->setText(WString::fromUTF8(dimxLabel_));
    dimx_ = new WSpinBox(formTable->elementAt(row, 1));
    dimx_->setMinimum(0);
    dimx_->setMaximum(90000);
    xLabel->setBuddy(dimx_);

    ++row;
    WLabel *yLabel = new WLabel(formTable->elementAt(row, 0));
    yLabel->setText(WString::fromUTF8(dimyLabel_));
    dimy_ = new WSpinBox(formTable->elementAt(row, 1));
    dimy_->setMinimum(0);
    dimy_->setMaximum(90000);
    yLabel->setBuddy(dimy_);

}

bool VanetAreaPropertyForm::validate()
{
    bool valid = true;
    if (dimx_->value() < 100 || dimy_->value() < 100) 
    {
        messages_.push_back(tr("vanet.property.form.area.error.dims").toUTF8());
        valid = false;
    }
    return valid;
}

std::vector<std::string> VanetAreaPropertyForm::feedbackMessages() 
{
    return messages_;
}

void VanetAreaPropertyForm::setPreselectedValues(const std::vector< boost::any >& values)
{
    try
    {
        int dimxVal = boost::any_cast<int>(values.at(0));
        int dimyVal = boost::any_cast<int>(values.at(1));
        Logger::entry("info") << "Received preselected X value: " << dimxVal << " and Y value" << dimyVal;
        dimx_->setValue(dimxVal);
        dimy_->setValue(dimyVal);
    }
    catch (std::out_of_range) 
    {
        Logger::entry("fatal") << "Fatal error. Parameter index for VanetAreaPropertyForm::setPreselectedValues out of range!";
    }
}


WStandardItem *VanetAreaPropertyForm::treeNode() 
{
    WStandardItem *result = new WStandardItem();
    result->setData(VanetArea);
    result->setText(tr("mappropertyeditor.group.general").toUTF8());

    result->appendRow(propertyRow(std::string("dimx"), tr("mappropertyeditor.group.general.dimx").toUTF8(), boost::lexical_cast<std::string>(dimx_->value())));
    result->appendRow(propertyRow(std::string("dimy"), tr("mappropertyeditor.group.general.dimy").toUTF8(), boost::lexical_cast<std::string>(dimy_->value())));

    return result;
}
