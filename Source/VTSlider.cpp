/*
  ==============================================================================

    VTSlider.cpp
    Created: 10 Jun 2020 11:03:53am
    Author:  Joseph Cresswell

  ==============================================================================
*/

#include "VTSlider.h"


VTSlider::VTSlider(ValueTree& tree) : mySlider(Slider::LinearHorizontal, Slider::TextBoxLeft), myTree(tree)
{
    mySlider.setName("Slidey");
    
    mySlider.addListener(this);
    
    addAndMakeVisible(&mySlider);
    
}

VTSlider::~VTSlider(){}

void VTSlider::paint(Graphics &g)
{
    
}

void VTSlider::resized()
{
    float height = getLocalBounds().getHeight();
    float width = getLocalBounds().getWidth();
    
    mySlider.setBounds(0, 0, width, height);
    
}

void VTSlider::sliderValueChanged(Slider *slider)
{
    static Identifier property("Double");
    
    float val = slider -> getValue();
    
    myTree.setProperty(property, val, nullptr); //null ptr is the undo manager
}


void VTSlider::updateSliderWithVT()
{
    static Identifier property("Double");
    
    float sliderVal = myTree.getProperty(property);
    
    mySlider.setValue(sliderVal);
}
