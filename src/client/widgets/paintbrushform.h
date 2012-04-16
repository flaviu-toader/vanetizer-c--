#ifndef PAINTBRUSHFORM_H
#define PAINTBRUSHFORM_H

#include <Wt/WTable>

class PaintBrush;

namespace Wt 
{
    class WSpinBox;
}

class PaintBrushForm : public Wt::WTable
{

public:
    PaintBrushForm(Wt::WContainerWidget* parent = 0);
private: 
    void downloadImage();
    void speedChanged(int newSpeed);
    
    PaintBrush* paintbrush_;
    Wt::WSpinBox* speed_;
};

#endif // PAINTBRUSHFORM_H
