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

#include "mapmakerpage.h"
#include "client/widgets/paintbrush.h"


MapMakerPage::MapMakerPage(WContainerWidget* parent): WContainerWidget(parent)
{
    resize(Wt::WLength::Auto, Wt::WLength::Auto);
    
    WTable *table = new WTable(this);
    
    paintbrush = new PaintBrush(710, 400, table->elementAt(0, 0));
    paintbrush->decorationStyle().setBorder(WBorder(WBorder::Solid, WBorder::Medium, WColor(black)));
    
    WTable *buttonTable = new WTable(table->elementAt(1,0));
    Wt::WPushButton *clearButton = new Wt::WPushButton(tr("button.clear"), buttonTable->elementAt(0,1));
    clearButton->setWidth(100);
    clearButton->setHeight(30);
    clearButton->clicked().connect(paintbrush, &PaintBrush::clear);
    
    Wt::WPushButton *undoButton = new Wt::WPushButton(tr("button.undo"), buttonTable->elementAt(0,2));
    undoButton->setWidth(100);
    undoButton->setHeight(30);
    undoButton->clicked().connect(paintbrush, &PaintBrush::undoLastAction);
    
    Wt::WPushButton *saveButton = new Wt::WPushButton(tr("button.save"), buttonTable->elementAt(0,3));
    saveButton->setWidth(100);
    saveButton->setHeight(30);
    saveButton->clicked().connect(this, &MapMakerPage::downloadImage);
    
    buttonTable->elementAt(0, 1)->setContentAlignment(AlignCenter);
    buttonTable->elementAt(0, 2)->setContentAlignment(AlignCenter);
    table->elementAt(1, 0)->setContentAlignment(AlignCenter);
}

void MapMakerPage::downloadImage()
{
    paintbrush->saveImage();
}


