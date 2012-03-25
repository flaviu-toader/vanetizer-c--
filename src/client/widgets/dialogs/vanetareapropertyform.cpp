
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

#include <Wt/WStandardItem>
#include <Wt/WSpinBox>
#include <Wt/WTable>
#include <Wt/WString>
#include <Wt/WLabel>

#include "logger.h"
#include "vanetareapropertyform.h"
#include "client/widgets/dialogs/abstractpropertyform.h"

using namespace Wt;

VanetAreaPropertyForm::VanetAreaPropertyForm(WContainerWidget* parent) 
{
    WTable *formTable = new WTable(this);
    int row = 0;

    WLabel *xLabel = new WLabel(formTable->elementAt(row, 0));
    xLabel->setText(WString::fromUTF8(tr("mappropertyeditor.group.general.dimx").toUTF8()));
    dimx_ = new WSpinBox(formTable->elementAt(row, 1));
    dimx_->setMinimum(0);
    dimx_->setMaximum(90000);
    xLabel->setBuddy(dimx_);

    ++row;
    WLabel *yLabel = new WLabel(formTable->elementAt(row, 0));
    yLabel->setText(WString::fromUTF8(tr("mappropertyeditor.group.general.dimy").toUTF8()));
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

void VanetAreaPropertyForm::setPreselectedValues(const std::map< std::string, boost::any >& values)
{
    int dimxVal = boost::any_cast<int>(*(values.find("dimx")));
    dimx_->setValue(dimxVal);
    int dimyVal = boost::any_cast<int>(*(values.find("dimy")));
    dimy_->setValue(dimyVal);
    Logger::entry("info") << "Received preselected X value: " << dimxVal << " and Y value" << dimyVal;
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
