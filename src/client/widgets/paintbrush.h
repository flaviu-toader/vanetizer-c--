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
#include <xml/xmlhelper.h>

using namespace Wt;

typedef std::pair<WPainterPath, int> ActionType;

struct Vertex 
{
    int id;
    int x;
    int y;
};

struct Edge
{
    int v1;
    int v2;
    int speed;
};

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
    
    Node imageNode(int dimX, int dimY, bool transform);
protected:
    virtual void paintEvent(WPaintDevice* paintDevice);
    
private:
    std::list< Vertex > transformVertices(int newDimX, int newDimY);
    std::list< Node > vertexNodes(const std::list< Vertex >& vlist);
    std::list< Node > edgeNodes();
    void mouseDown(const WMouseEvent& e);
    
    WPainterPath path_;
    WColor color_;
    int currentSpeed_;
    int interactionCount_;
    std::vector< WPainterPath > actions_;
    std::list< Vertex > vertexList_;
    std::list< Edge > edgeList_;
    bool undo_;
    
};

#endif // PAINTBRUSH_H_
