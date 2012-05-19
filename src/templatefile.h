#ifndef TEMPLATEFILE_H
#define TEMPLATEFILE_H

#include <string>
#include <map>

class TemplateFile
{
public:
    TemplateFile(const std::string& filename);
    void render(const std::string& filename);
    void replaceString(const std::string& varName, const std::string& value);
private:
    std::string contents_;
    std::map< std::string, std::string > bindings_;
};

#endif // TEMPLATEFILE_H
