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


#include <boost/lexical_cast.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include "paintbrush.h"

#include "logger.h"

#include <Wt/WCssDecorationStyle>
#include <Wt/WPainter>
#include <Wt/WPainterPath>
#include <Wt/WPointF>
#include <Wt/WRectF>
#include <Wt/WSvgImage>
#include <Wt/WImage>
#include <Wt/WContainerWidget>

PaintBrush::PaintBrush(int width, int height, WContainerWidget *parent)
: WPaintedWidget(parent)
{
    setSelectable(false);
    interactionCount_ = 0;
    undo_ = false;
    
//     setPositionScheme(Absolute);
    resize(WLength(width), WLength(height));
    
    decorationStyle().setCursor("icons/pencil.cur", CrossCursor);
    
    mouseWentDown().connect(this, &PaintBrush::mouseDown);
    
    color_ = WColor(black);
    
    // setPreferredMethod(InlineSvgVml);
}

void PaintBrush::paintEvent(WPaintDevice *paintDevice)
{
    WPainter painter(paintDevice);
    painter.setRenderHint(WPainter::Antialiasing);
    
    WPen pen;
    pen.setWidth(3);
    pen.setColor(color_);
    painter.setPen(pen);
    if (!undo_) 
    {
        painter.drawPath(path_);
    } 
    else 
    {
        for(std::vector< WPainterPath >::iterator it = actions_.begin(); it != actions_.end(); ++it) 
        {
            WPainterPath p = *it;
            painter.drawPath(p);
        }
        undo_ = false;
        update(PaintUpdate);
    }
    path_ = WPainterPath(path_.currentPosition());
}

void PaintBrush::mouseDown(const WMouseEvent& e)
{
    Coordinates c = e.widget();
    if (interactionCount_ % 2 == 0) {
        path_ = WPainterPath(WPointF(c.x, c.y));
        Vertex v;
        v.id = interactionCount_;
        v.x = c.x;
        v.y = c.y;
        vertexList_.push_back(v);
        interactionCount_++;
        path_.addRect(c.x, c.y, 1, 1);
        update(PaintUpdate);
    } else {
        path_.lineTo(c.x, c.y);
        Vertex v;
        v.id = interactionCount_;
        v.x = c.x;
        v.y = c.y;
        vertexList_.push_back(v);
        Edge e;
        e.v1 = v.id - 1;
        e.v2 = v.id;
        e.speed = currentSpeed_;
        edgeList_.push_back(e);
        interactionCount_++;
        path_.addRect(c.x, c.y, 1, 1);
        actions_.push_back(path_);
        update(PaintUpdate);
    }
}

void PaintBrush::undoLastAction()
{
    if (!actions_.empty()) 
    {
        Logger::entry("info") << "User undid one action.";
        actions_.pop_back();
        update();
        undo_ = true;
    }
}

Node PaintBrush::imageNode(int dimX, int dimY, bool transform)
{
    Node result("extension");
    Attribute cAttr("class", "eurecom.usergraph.UserGraph");
    result.addAttribute(cAttr);
    Logger::entry("info") << "dimX = " << dimX;
    Logger::entry("info") << "dimY = " << dimY;
    if (!actions_.empty()) 
    {
        if (dimX == 0 || dimY == 0)
        {
            Logger::entry("error") << "No area defined for the user graph.";
            return result;
        }
        if (transform)
            result.addChildren(vertexNodes(transformVertices(dimX, dimY)));
        else
            result.addChildren(vertexNodes(vertexList_));
        result.addChildren(edgeNodes());
    }
    return result;
}

std::list< Vertex > PaintBrush::transformVertices(int newDimX, int newDimY)
{
    std::list< Vertex > result;
    std::list< Vertex >::iterator it;
    int oldDimX = (int) this->width().value();
    int oldDimY = (int) this->height().value();
    for (it = vertexList_.begin(); it != vertexList_.end(); ++it)
    {
        Vertex v;
        v.id = it->id;
        v.x = (int) ((newDimX * it->x) / oldDimX);
        v.y = (int) ((newDimY * it->y) / oldDimY);
        result.push_back(v);
    }
    return result;
}

std::list< Node > PaintBrush::vertexNodes(const std::list< Vertex >& vlist)
{
    std::list< Node > result;
    std::list< Vertex >::const_iterator it;
    for (it = vlist.begin(); it != vlist.end(); ++it)
    {
        Node v("vertex");
        Node i("id");
        i.value(boost::lexical_cast<std::string>(it->id));
        Node x("x");
        x.value(boost::lexical_cast<std::string>(it->x));
        Node y("y");
        y.value(boost::lexical_cast<std::string>(it->y));
        v.addChild(i);
        v.addChild(x);
        v.addChild(y);
        result.push_back(v);
    }
    return result;
}

std::list< Node > PaintBrush::edgeNodes()
{
    std::list< Node > result;
    std::list< Edge >::iterator it;
    for (it = edgeList_.begin(); it != edgeList_.end(); ++it)
    {
        Node e("edge");
        Node v1("v1");
        v1.value(boost::lexical_cast<std::string>(it->v1));
        Node v2("v2");
        v2.value(boost::lexical_cast<std::string>(it->v2));
        Node s("speed");
        s.value(boost::lexical_cast<std::string>(it->speed));
        e.addChild(v1);
        e.addChild(v2);
        e.addChild(s);
        result.push_back(e);
    }
    return result;
}

// std::string PaintBrush::imageAsXml()
// {
// //     std::stringstream ss;
// //     ss << "";
// //     if (!actions_.empty())
// //     {
// //         Wt::WSvgImage imageDevice(this->width(), this->height());
// //         WPainter painter(&imageDevice);
// //         for (std::vector<WPainterPath>::iterator it = actions_.begin(); it != actions_.end(); ++it) 
// //         {
// //             painter.drawPath(*it);
// //         }
// //         painter.end();
// //         imageDevice.write(ss);
// //     }
// //     return ss.str();
// }
// 
// void PaintBrush::(std::string img)
// {
//     if (!img.empty())
//     {
//         Logger::entry("info") << "Creating svg file...";
//         std::string filename = "resources/test.svg";
//         std::ofstream outfile(filename.c_str());
//         outfile << img;
//         outfile.close();
// 
//         Logger::entry("info") << "Painting to canvas...";
//         
//         WImage* img = new WImage(filename, static_cast< WContainerWidget* >(this->parent()));
// //         img->setPositionScheme(Absolute);
//         img->resize(this->width(), this->height());
//         
// //         WSvgImage imageDevice(this->width(), this->height(), this);
// //         WRectF rect = WRectF(0, 0, this->width().value(), this->height().value());
// //         imageDevice.drawImage(rect, filename, this->width().value(), this->height().value(), rect);
// //         WPainter painter(&imageDevice);
// //         painter.drawImage(0, 0, WPainter::Image(filename, this->width().value(), this->height().value()));
// //         painter.end();
// //         update(PaintUpdate);
// //         imageDevice.done();
//     }
// }
