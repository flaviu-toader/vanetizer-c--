#include <Wt/WTable>
#include <Wt/WColor>
#include <Wt/WBorder>
#include <Wt/WCssDecorationStyle>
#include <Wt/WSpinBox>
#include <Wt/WLabel>
#include <Wt/WHBoxLayout>
#include <Wt/WPushButton>

#include "paintbrushform.h"
#include "paintbrush.h"
#include "logger.h"

using namespace Wt;
using namespace std;

PaintBrushForm::PaintBrushForm(WContainerWidget* parent) : WTable(parent)
{
    int row = 0;
    WLabel* l = new WLabel(tr("painbrushform.speed.intro")/*, elementAt(row, 0)*/);
    ++row;
    WContainerWidget* canvasContainer = new WContainerWidget(elementAt(row, 0));
    canvasContainer->setPositionScheme(Relative);
    paintbrush_ = new PaintBrush(640, 480, canvasContainer);
    paintbrush_->decorationStyle().setBorder(WBorder(WBorder::Solid, WBorder::Medium, WColor(black)));
    
    ++row;
    WHBoxLayout* hbx = new WHBoxLayout(elementAt(row, 0));
    l = new WLabel(tr("painbrushform.speed.label"));
    hbx->addWidget(l);
    speed_ = new WSpinBox;
    l->setBuddy(speed_);
    hbx->addWidget(speed_);
    speed_->setHeight(16);
    speed_->setWidth(40);
    speed_->setMaximum(180);
    speed_->setMinimum(30);
    speed_->setValue(50);
    speed_->valueChanged().connect(this, &PaintBrushForm::speedChanged);
    elementAt(row, 0)->setLayout(hbx, AlignTop | AlignLeft);
    
    ++row;
    WTable* buttonTable = new WTable(elementAt(row, 0));
    int bcol = 0;
    ++bcol;
    WPushButton *clearButton = new WPushButton(tr("button.clear"), buttonTable->elementAt(0, bcol));
    clearButton->setWidth(100);
    clearButton->setHeight(30);
    clearButton->clicked().connect(paintbrush_, &PaintBrush::clear);
    
    ++bcol;
    WPushButton *undoButton = new WPushButton(tr("button.undo"), buttonTable->elementAt(0, bcol));
    undoButton->setWidth(100);
    undoButton->setHeight(30);
    undoButton->clicked().connect(paintbrush_, &PaintBrush::undoLastAction);
    
    //++bcol;
    //WPushButton *saveButton = new WPushButton(tr("button.save"), buttonTable->elementAt(0, bcol));
    //saveButton->setWidth(100);
    //saveButton->setHeight(30);
    //saveButton->clicked().connect(this, &PaintBrushForm::downloadImage);
    
    buttonTable->elementAt(0, 1)->setContentAlignment(AlignCenter);
    buttonTable->elementAt(0, 2)->setContentAlignment(AlignCenter);
    elementAt(row, 0)->setContentAlignment(AlignCenter);
    
    paintbrush_->setCurrentSpeed(speed_->value());
}

void PaintBrushForm::speedChanged(int newSpeed)
{
    paintbrush_->setCurrentSpeed(newSpeed);
}

Node PaintBrushForm::imageNode(int dimX, int dimY)
{
    return paintbrush_->imageNode(dimX, dimY, true);
}

// string PaintBrushForm::imageAsSvg()
// {
//     return paintbrush_->imageAsXml();
// }
// 
// void PaintBrushForm::imageAsSvg(string img)
// {
//     paintbrush_->imageAsSvg(img);
// }
