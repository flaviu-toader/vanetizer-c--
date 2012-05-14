#ifndef XMLHELPER_H_
#define XMLHELPER_H_

#include <string>
#include <list>
#include <boost/concept_check.hpp>

/*! 
 * Defines some classes that help in converting WStandardItems from the treeview to xml.
 */

//! The attribute class associate a name and a value for each xml attribute of each node.
class Attribute
{
public:
    Attribute(std::string name, std::string value);
    void name(const std::string& n);
    void value(const std::string& v);
    std::string name() const;
    std::string value() const;
private:
    std::string name_;
    std::string value_;
};

//! The node has name, children nodes and other attributes associated to it.
class Node
{
public:
    Node(std::string name);
    void addAttribute(const Attribute& a);
    std::list< Attribute > attributes() const;
    void addChild(const Node& n);
    void addChildren(const std::list< Node >& children);
    void replaceChild(const Node& o, const Node& n);
    void replaceChildren(const std::list< Node >& ov, const std::list< Node >& nv);
    std::list< Node > children() const;
    void name(const std::string& n);
    std::string name() const;
    void value(const std::string& v);
    std::string value() const;
    bool hasValue() const;
private:
    std::list< Attribute > attributes_;
    std::list< Node > children_;
    std::string name_;
    std::string value_;
};

#endif