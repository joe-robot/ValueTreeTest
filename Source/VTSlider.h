/*
  ==============================================================================

    VTSlider.h
    Created: 10 Jun 2020 11:03:53am
    Author:  Joseph Cresswell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class VTSlider : public Component,
                 public Slider::Listener //May not need if use value tree correct?
{
public:
    VTSlider(ValueTree& tree);
    ~VTSlider();
    
    void paint(Graphics &g) override;
    void resized() override;
    
    
    void sliderValueChanged(Slider* slider) override;
    
    void updateSliderWithVT();
    
private:
    Slider mySlider;
    
    ValueTree& myTree;
    //Could use atomics to store info
};
