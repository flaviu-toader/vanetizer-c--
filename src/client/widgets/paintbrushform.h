#ifndef PAINTBRUSHFORM_H
#define PAINTBRUSHFORM_H

#include <vector>
#include <Wt/WTable>
#include "client/widgets/paintbrush.h"
#include <xml/xmlhelper.h>

namespace Wt 
{
    class WSpinBox;
}

class PaintBrushForm : public Wt::WTable
{

public:
    PaintBrushForm(Wt::WContainerWidget* parent = 0);
    Node transformedImageNode(int dimX, int dimY);
    Node imageNode();
    void loadImage(const Node& root);
private: 
    void speedChanged(int newSpeed);
    
    PaintBrush* paintbrush_;
    Wt::WSpinBox* speed_;
};

#endif // PAINTBRUSHFORM_H
