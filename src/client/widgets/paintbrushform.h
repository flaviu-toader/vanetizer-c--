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
    Node imageNode(int dimX, int dimY);
//     //! Get the image map as an svg string.
//     std::string imageAsSvg();
//     //! Set the image map from a string representing valid svg markup.
//     void imageAsSvg(std::string img);
private: 
    void speedChanged(int newSpeed);
    
    PaintBrush* paintbrush_;
    Wt::WSpinBox* speed_;
};

#endif // PAINTBRUSHFORM_H
