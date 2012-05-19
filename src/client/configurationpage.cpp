/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Flaviu Toader <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <vector>
#include <list>
#include <functional>
#include <numeric>

#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WCssDecorationStyle>
#include <Wt/WBorder>
#include <Wt/WColor>
#include <Wt/WTable>
#include <Wt/WMessageBox>
#include <Wt/WStandardItemModel>
#include <Wt/WComboBox>
#include <Wt/WLabel>
#include <Wt/WContainerWidget>

#include "configurationpage.h"
#include "client/widgets/paintbrushform.h"
#include "client/widgets/mappropertyeditor.h"

using namespace Wt;

ConfigurationPage::ConfigurationPage(WContainerWidget* parent): 
    WContainerWidget(parent)
{
    resize(Wt::WLength::Auto, Wt::WLength::Auto);
    
    setContentAlignment(AlignCenter);
    WTable* table = new WTable(this);
    int row = 0;
    
    WLabel* l = new WLabel(tr("mapmaker.combo.label"), table->elementAt(row, 0));
    mapCombo_ = new WComboBox(table->elementAt(row, 0));
    mapCombo_->addItem(tr("mapmaker.combo.random"));
    mapCombo_->addItem(tr("mapmaker.combo.user"));
    l->setBuddy(mapCombo_);
    mapCombo_->activated().connect(this, &ConfigurationPage::mapComboChanged);
    
    ++row;
    // only attach the form to the table if the correct option is selected in the combo.
    formContainer_ = new WContainerWidget(table->elementAt(row, 0));
    paintBrushForm_ = new PaintBrushForm;
    
    ++row;
    Wt::WStandardItemModel *model = MapPropertyEditor::createModel(this);
    mpe_ = new MapPropertyEditor(this, model);
    table->elementAt(row, 0)->addWidget(mpe_);
    table->elementAt(row, 0)->setRowSpan(2);
    table->elementAt(row, 0)->setPadding(25);
    
    setOverflow(OverflowAuto);
}

void ConfigurationPage::mapComboChanged(int index)
{
    switch(index)
    {
        case 1:
            formContainer_->clear();
            formContainer_->addWidget(paintBrushForm_);
            break;
        default:
            formContainer_->clear();
    }
}

bool ConfigurationPage::validate(VanetConfigurator& cfg)
{
    Node root = mpe_->getModelNode();
    if (mapCombo_->currentIndex() == 1) 
    {
        std::pair< int, int > dims = getDims(root);
        Node userGraph = paintBrushForm_->saveImage(dims.first, dims.second);
        root.addChild(userGraph);
    }
    cfg.modelNode(root);
    std::vector< WString > messages;
    if(cfg.validate(messages)) 
    {
        return true;
    }
    else
    {
       if (!messages.empty())
       {
           WMessageBox::show(tr("application.error"), std::accumulate(messages.begin(), messages.end(), WString("")), Ok);
       }
    }
    return false;
}


void ConfigurationPage::saveClicked()
{
    VanetConfigurator cfg;
    if (validate(cfg))
    {
        cfg.save();
    }
    
}

std::pair< int, int > ConfigurationPage::getDims(Node n)
{
    std::pair< int, int > result = std::make_pair< int, int >(0, 0);
    // we know nodes 'dimx' and 'dimy' should be on the first level, so we won't go any deeper.
    std::list< Node > children = n.children();
    std::list< Node >::iterator it = children.begin();
    for (; it != children.end(); ++it)
    {
        if (it->name() == std::string("dimx"))
            result.first = boost::lexical_cast<int>(std::string(it->value()));
        if (it->name() == std::string("dimy"))
            result.second = boost::lexical_cast<int>(std::string(it->value()));
        if (result.first != 0 && result.second != 0)
            break;
    }
    return result;
}


