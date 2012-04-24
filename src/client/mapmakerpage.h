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


#ifndef MAPMAKERPAGE_H
#define MAPMAKERPAGE_H

#include <Wt/WContainerWidget>

class PaintBrushForm;

namespace Wt
{
    class WComboBox;
    class WTable;
}

class MapMakerPage : public Wt::WContainerWidget
{
public:
    MapMakerPage(WContainerWidget* parent = 0);
    
private:
    void mapComboChanged(int index);
    
    Wt::WContainerWidget* formContainer_;
    Wt::WComboBox* mapCombo_;
    PaintBrushForm* paintBrushForm_;
};

#endif // MAPMAKERPAGE_H
