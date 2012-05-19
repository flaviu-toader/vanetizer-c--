#include <iostream>
#include <fstream>

#include "templatefile.h"
#include "logger.h"

using namespace std;
using namespace Wt;

TemplateFile::TemplateFile(const string& filename)
{
    ifstream templatefile(filename.c_str());
    if (templatefile.is_open())
    {
        stringstream ss;
        ss << templatefile.rdbuf();
        contents_ = ss.str();
        templatefile.close();
    }
    else 
    {
        Logger::entry("error") << "Unable to open template file " << filename;
        contents_ = "";
    }
}

void TemplateFile::replaceString(const string& varName, const string& value)
{
    string var = string("${") + varName + string("}");
    contents_ = contents_.replace(contents_.find(var), var.size(), value);
}

void TemplateFile::render(const string& filename)
{
    ofstream outfile(filename.c_str());
    if (outfile.is_open() && contents_ != "")
    {
        outfile << contents_;
        outfile.close();
    }
    else
    {
        Logger::entry("info") << "Is contents empty? " << contents_.empty();
        Logger::entry("error") << "Unable to open output file " << filename;
    }
}
