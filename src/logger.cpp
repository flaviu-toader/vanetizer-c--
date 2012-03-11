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


#include <Wt/WLogger>
#include <iostream>
#include <sstream>

#include "logger.h"

bool Logger::instanceFlag = false;
Wt::WLogger* Logger::logger = NULL;

Wt::WLogger *Logger::instance() 
{
    if (!instanceFlag) 
    {
        logger = new Wt::WLogger();
        logger->addField("datetime", false);
        logger->addField("type", false);
        logger->addField("message", true);
        logger->setFile("../logs/vanetizer.log");
        logger->configure("* debug:wthttp");
        instanceFlag = true;
        return logger;
    }
    else 
    {
        return logger;
    }
}

void Logger::entry(std::string level, std::string message) 
{
    instance()->entry(level) << Wt::WLogger::timestamp << Wt::WLogger::sep << message;
}

Wt::WLogEntry Logger::entry(std::string level) 
{
    return instance()->entry(level) << Wt::WLogger::timestamp << Wt::WLogger::sep;
}