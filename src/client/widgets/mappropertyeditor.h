/*
 *    <one line to give the program's name and a brief idea of what it does.>
 *    Copyright (C) 2012  Flaviu Toader <email>
 * 
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 * 
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 * 
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAPPROPERTYEDITOR_H_
#define MAPPROPERTYEDITOR_H_

#include <Wt/WContainerWidget>
#include <Wt/WFlags>
#include <Wt/WModelIndex>
#include <boost/any.hpp>

// forward declarations
namespace Wt {
    class WStandardItem;
    class WStandardItemModel;
    class WTreeView;
    class WString;
}

//! A treeview allowing to set/change properties for VANET maps.
/*!
 * This class extends the Wt::WContainerWidget, and creates a static mvc tree containing the editable properties of
 * a VANET map. 
 */
class MapPropertyEditor : public Wt::WContainerWidget
{
public:
    //! Constructor takes the model to be used.
    /*!
     * This property editor constructor takes in a Wt::StandardItemModel as the model to be rendered using the treeview.
     */
    MapPropertyEditor(Wt::WStandardItemModel *model);

    //! Get the treeview.
    /*! 
     * Returns the treeview used in this property editor.
     */
    Wt::WTreeView *getTreeView() const { return treeView; }

    //! Static method that generates the model for our map property editor.
    /*!
     * A static method that creates the model for the treeview. This model will contain all the necessary properties
     * for a VANET map.
     */
    static Wt::WStandardItemModel *createModel(WObject *parent);

private:
    static Wt::WStandardItem *groupItem(const std::string& groupName);
    static std::vector<Wt::WStandardItem *> propertyItem(const std::string& name, const boost::any& data);

    Wt::WStandardItemModel *model;
    Wt::WTreeView *treeView;

};

#endif // MAPPROPERTYEDITOR_H_
