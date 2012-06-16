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

void PaintBrush::drawActions(WPainter& painter)
{
    for(std::vector< WPainterPath >::iterator it = actions_.begin(); it != actions_.end(); ++it)
    {
        WPainterPath p = *it;
        painter.drawPath(p);
    }

}


void PaintBrush::paintEvent(WPaintDevice *paintDevice)
{
    WPainter painter(paintDevice);
    painter.setRenderHint(WPainter::Antialiasing);

    WPen pen;
    pen.setWidth(3);
    pen.setColor(color_);
    painter.setPen(pen);
    
    if (interactionCount_ == 0 && !actions_.empty()) {
        drawActions(painter);
        interactionCount_ = vertexList_.size();
    }
    
    if (!undo_)
    {
        painter.drawPath(path_);
    }
    else
    {
        drawActions(painter);
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

void PaintBrush::loadImage(const Node& root)
{
    update();
    interactionCount_ = 0;
    actions_.clear();
    vertexList_.clear();
    edgeList_.clear();
    std::list< Node > children = root.children();
    std::list< Node >::iterator it;
    for (it = children.begin(); it != children.end(); ++it)
    {
        if (it->name() == "vertex") vertexList_.push_back(extractVertex(it->children()));
        if (it->name() == "edge") edgeList_.push_back(extractEdge(it->children()));
    }

    // now iterate the edges and update the image.
    std::list< Edge >::iterator eit;
    for (eit = edgeList_.begin(); eit != edgeList_.end(); ++eit)
    {
        Vertex v1 = lookup(eit->v1);
        path_ = WPainterPath(WPointF(v1.x, v1.y));
        path_.addRect(v1.x, v1.y, 1, 1);
        Vertex v2 = lookup(eit->v2);
        path_.lineTo(v2.x, v2.y);
        path_.addRect(v2.x, v2.y, 1, 1);
        actions_.push_back(path_);
    }
    update(PaintUpdate);
}

Vertex PaintBrush::extractVertex(const std::list< Node >& nodeList)
{
    Vertex v;
    for (std::list< Node >::const_iterator vit = nodeList.begin(); vit != nodeList.end(); ++vit)
    {
        if (vit->name() == "id")
        {
            try {
                v.id = boost::lexical_cast<int>(vit->value());
            } catch (boost::bad_lexical_cast const&) {
                Logger::entry("error") << "Bad string for vertex id: " << vit->value();
                // throwing a std::exception or its derivatives will restart the application, which is what we want if the string's bad.
                throw std::exception();
            }
        }
        if (vit->name() == "x")
        {
            try {
                v.x = boost::lexical_cast< int >(vit->value());
            } catch (boost::bad_lexical_cast const&) {
                Logger::entry("error") << "Bad string for vertex x coordinate: " << vit->value();
                throw std::exception();
            }
        }
        if (vit->name() == "y")
        {
            try {
                v.y = boost::lexical_cast< int >(vit->value());
            } catch (boost::bad_lexical_cast const&) {
                Logger::entry("error") << "Bad string for vertex y coordinate: " << vit->value();
                throw std::exception();
            }
        }
    }
    return v;
}

Edge PaintBrush::extractEdge(const std::list< Node >& nodeList)
{
    Edge e;
    for (std::list< Node >::const_iterator eit = nodeList.begin(); eit != nodeList.end(); ++eit)
    {
        if (eit->name() == "v1")
        {
            try {
                e.v1 = boost::lexical_cast< int >(eit->value());
            } catch (boost::bad_lexical_cast const &) {
                Logger::entry("error") << "Bad string for edge's initial vertex id: " << eit->value();
                throw std::exception();
            }
        }
        if (eit->name() == "v2")
        {
            try {
                e.v2 = boost::lexical_cast< int >(eit->value());
            } catch (boost::bad_lexical_cast const &) {
                Logger::entry("error") << "Bad string for edge's terminal vertex id: " << eit->value();
                throw std::exception();
            }
        }
        if (eit->name() == "speed")
        {
            try {
                e.speed = boost::lexical_cast< int >(eit->value());
            } catch (boost::bad_lexical_cast const &) {
                Logger::entry("error") << "Bad string for edge's speed: " << eit->value();
                throw std::exception();
            }
        }
    }
    return e;
}

Vertex PaintBrush::lookup(int id)
{
    std::list< Vertex >::iterator it;
    for (it = vertexList_.begin(); it != vertexList_.end(); ++it)
    {
        if (it->id == id)
            return (*it);
    }
    // if we are here, we are going to have a bad time.
    Logger::entry("error") << "The vertex lookup failed!";
    Vertex v;
    v.id = -1;
    v.x = -1;
    v.y = -1;
    return v;
}



