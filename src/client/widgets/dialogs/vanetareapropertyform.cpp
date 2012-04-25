
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
#include "client/xmlhelper.h"
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

bool VanetAreaPropertyForm::validate(std::vector< std::string >& messages)
{
    bool valid = true;
    if (dimx_->value() < 100 || dimy_->value() < 100) 
    {
        messages.push_back(tr("vanet.property.form.area.error.dims").toUTF8());
        valid = false;
    }
    return valid;
}

void VanetAreaPropertyForm::setPreselectedValues(const std::map< std::string, boost::any >& values)
{
    setPreselectedIntegerValue("dimx", values, dimx_);
    setPreselectedIntegerValue("dimy", values, dimy_);
}


WStandardItem *VanetAreaPropertyForm::treeNode(std::vector< Node >& nodes) 
{
    WStandardItem *result = new WStandardItem(tr("mappropertyeditor.group.general"));
    result->setData(VanetArea);
    
    Node xNode = Node("dimx");
    xNode.value(boost::lexical_cast<std::string>(dimx_->value()));
    nodes.push_back(xNode);
    result->appendRow(propertyRow(std::string("dimx"), tr("mappropertyeditor.group.general.dimx").toUTF8(), boost::lexical_cast<std::string>(dimx_->value())));
    Node yNode = Node("dimy");
    yNode.value(boost::lexical_cast<std::string>(dimy_->value()));
    nodes.push_back(yNode);
    result->appendRow(propertyRow(std::string("dimy"), tr("mappropertyeditor.group.general.dimy").toUTF8(), boost::lexical_cast<std::string>(dimy_->value())));

    return result;
}

