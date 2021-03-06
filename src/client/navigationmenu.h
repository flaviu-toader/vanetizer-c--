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


#ifndef NAVIGATIONMENU_H
#define NAVIGATIONMENU_H

#include <Wt/WContainerWidget>
#include <Wt/WStackedWidget>

class NavigationMenu : public Wt::WContainerWidget
{
public:
    NavigationMenu(Wt::WStackedWidget* contents, WContainerWidget* parent = 0);
    
};

#endif // NAVIGATIONMENU_H
