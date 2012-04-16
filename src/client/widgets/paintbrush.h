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

typedef std::pair<WPainterPath, int> EdgeType;

class PaintBrush : public WPaintedWidget
{
public:
    PaintBrush(int width, int height, WContainerWidget *parent = 0);
    
    void clear() 
    {
        if (!actions_.empty()) 
        {
            actions_.clear();
        }
        update();
    }
    
    void setColor(const WColor& c) 
    {
        color_ = c;
    }
    
    void setCurrentSpeed(int speed) 
    {
        currentSpeed_ = speed;
    }
    
    void undoLastAction();
    
    void saveImage();
protected:
    virtual void paintEvent(WPaintDevice* paintDevice);
    
private:
    WPainterPath path_;
    WColor color_;
    int currentSpeed_;
    int interactionCount_;
    std::vector<EdgeType> actions_;
    bool undo_;
    
    void mouseDown(const WMouseEvent& e); 
};

#endif // PAINTBRUSH_H_
