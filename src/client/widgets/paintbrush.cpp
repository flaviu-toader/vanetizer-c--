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

#include "paintbrush.h"

#include "logger.h"

#include <Wt/WCssDecorationStyle>
#include <Wt/WPainter>
#include <Wt/WPainterPath>
#include <Wt/WPointF>
#include <Wt/WRectF>
#include <Wt/WSvgImage>
/*#include <Wt/WTransform>*/

PaintBrush::PaintBrush(int width, int height, WContainerWidget *parent)
: WPaintedWidget(parent)
{
    setSelectable(false);
    interactionCount = 0;
    undo = false;
    
    resize(WLength(width), WLength(height));
    
    decorationStyle().setCursor("icons/pencil.cur", CrossCursor);
    
    mouseWentDown().connect(this, &PaintBrush::mouseDown);
    
    color = WColor(black);
    
    // setPreferredMethod(InlineSvgVml);
}

void PaintBrush::paintEvent(WPaintDevice *paintDevice)
{
    WPainter painter(paintDevice);
    painter.setRenderHint(WPainter::Antialiasing);
    
    WPen pen;
    pen.setWidth(3);
    pen.setColor(color);
    painter.setPen(pen);
    if (!undo) 
    {
        painter.drawPath(path);
    } 
    else 
    {
        for(std::vector<WPainterPath>::iterator it = actions.begin(); it != actions.end(); ++it) 
        {
            painter.drawPath(*it);
        }
        undo = false;
        update(PaintUpdate);
    }
    path = WPainterPath(path.currentPosition());
}

void PaintBrush::mouseDown(const WMouseEvent& e)
{
    Coordinates c = e.widget();
    if (interactionCount == 0) {
        path = WPainterPath(WPointF(c.x, c.y));
        interactionCount++;
        path.addRect(c.x, c.y, 1, 1);
        update(PaintUpdate);
    } else {
        path.lineTo(c.x, c.y);
        interactionCount = 0;
        path.addRect(c.x, c.y, 1, 1);
        actions.push_back(path);
        update(PaintUpdate);
    }
}

void PaintBrush::undoLastAction()
{
    if (!actions.empty()) 
    {
        Logger::entry("info", "User undid one action.");
        actions.pop_back();
        update();
        undo = true;
    }
}

void PaintBrush::saveImage(/*const WTransform &transform*/)
{
    if (!actions.empty()) 
    {
        // TODO: instead of painting to an svg image, 'dump' the actions in an xml file 
        // with a compatible format to VanetMobiSim
        Wt::WSvgImage imageDevice(this->width(), this->height());
        WPainter painter(&imageDevice);
        for (std::vector<WPainterPath>::iterator it = actions.begin(); it != actions.end(); ++it) 
        {
            painter.drawPath(*it);
        }
        //painter.setWorldTransform(transform);
        painter.end();
        std::ofstream f("test.svg");
        imageDevice.write(f);
    }
}



