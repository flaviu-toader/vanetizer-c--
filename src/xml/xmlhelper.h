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
    //! Create new node with given string.
    Node(std::string name);
    //! Add attribute to node.
    void addAttribute(const Attribute& a);
    //! Get list of attributes.
    std::list< Attribute > attributes() const;
    //! Add node n as child at the end of the list.
    void addChild(const Node& n);
    //! Add node n as child at given position.
    void addChild(const Node& n, std::list< Node >::iterator pos);
    //! Add list of children nodes at the end of the children's list.
    void addChildren(const std::list< Node >& children);
    //! Add list of children nodes at given position.
    void addChildren(const std::list< Node >& children, std::list< Node >::iterator pos);
    //! Remove child given by name from the children's list and return the position.
    std::list< Node >::iterator removeChild(const std::string& name);
    //! Get list of children.
    std::list< Node > children() const;
    //! Set the name of the node.
    void name(const std::string& n);
    //! Get the name of the node.
    std::string name() const;
    //! Set a value for the node (not mandatory).
    void value(const std::string& v);
    //! Get value of this node.
    std::string value() const;
    //! Check if this node has a value.
    bool hasValue() const;
private:
    std::list< Attribute > attributes_;
    std::list< Node > children_;
    std::string name_;
    std::string value_;
};

#endif