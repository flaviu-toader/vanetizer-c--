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


#ifndef PAINTBRUSH_H_
#define PAINTBRUSH_H_

#include <Wt/WPaintedWidget>
#include <Wt/WPainterPath>
#include <Wt/WColor>
#include <Wt/WEvent>

#include <vector>

using namespace Wt;

class PaintBrush : public WPaintedWidget
{
public:
    PaintBrush(int width, int height, WContainerWidget *parent = 0);
    
    void clear() {
        if (!actions.empty()) 
        {
            actions.clear();
        }
        update();
    }
    
    void setColor(const WColor& c) {
        color = c;
    }
    
    void undoLastAction();
    
    void saveImage();
protected:
    virtual void paintEvent(WPaintDevice* paintDevice);
    
private:
    WPainterPath path;
    WColor color;
    int interactionCount;
    std::vector<WPainterPath> actions;
    bool undo;
    
    void mouseDown(const WMouseEvent& e); 
};

#endif // PAINTBRUSH_H_
