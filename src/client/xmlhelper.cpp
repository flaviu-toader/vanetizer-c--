#include <string>
#include <vector>

#include "xmlhelper.h"

using namespace std;

Attribute::Attribute(string name, string value) :
    name_(name),
    value_(value)
{
}

void Attribute::name(const string& n)
{
    name_ = n;
}

string Attribute::name() const
{
    return name_;
}

void Attribute::value(const string& v)
{
    value_ = v;
}

string Attribute::value() const
{
    return value_;
}

Node::Node(string name) :
    name_(name)
{
}

void Node::addAttribute(const Attribute& a)
{
    attributes_.push_back(a);
}

void Node::addChild(const Node& n)
{
    children_.push_back(n);
}

void Node::addChildren(const vector< Node >& children)
{
    children_.insert(children_.end(), children.begin(), children.end());
}


vector< Attribute > Node::attributes() const
{
    return attributes_;
}

vector< Node > Node::children() const
{
    return children_;
}

void Node::name(const string& n)
{
    name_ = n;
}

string Node::name() const
{
    return name_;
}

void Node::value(const string& v)
{
    value_ = v;
}

string Node::value() const
{
    return value_;
}

bool Node::hasValue() const
{
    return !value_.empty();
}

