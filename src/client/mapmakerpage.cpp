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

#include "mapmakerpage.h"
#include "client/widgets/paintbrushform.h"
#include "client/widgets/mappropertyeditor.h"

using namespace Wt;

MapMakerPage::MapMakerPage(WContainerWidget* parent): WContainerWidget(parent)
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
    mapCombo_->activated().connect(this, &MapMakerPage::mapComboChanged);
    
    ++row;
    // only attach the form to the table if the correct option is selected in the combo.
    formContainer_ = new WContainerWidget(table->elementAt(row, 0));
    paintBrushForm_ = new PaintBrushForm;
    
    ++row;
    Wt::WStandardItemModel *model = MapPropertyEditor::createModel(this);
    MapPropertyEditor *mpe = new MapPropertyEditor(this, model);
    table->elementAt(row, 0)->addWidget(mpe);
    table->elementAt(row, 0)->setRowSpan(2);
    table->elementAt(row, 0)->setPadding(25);
    
    setOverflow(OverflowAuto);
}

void MapMakerPage::mapComboChanged(int index)
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

