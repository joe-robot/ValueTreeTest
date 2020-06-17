/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "VTSlider.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public TextEditor::Listener,
                        public ValueTree::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
    void getValueTreeVals();
    
    void exportValueTreeToXML();
    
    bool loadXMLfromFile();
    
    void textEditorTextChanged (TextEditor &editor) override;
    
    void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property) override;

private:
    //==============================================================================
    // Your private member variables go here...

    
    ValueTree testTree;
    
    TextButton getValButton;
    
    TextEditor myEditor;
    
    std::atomic<float> sliderVal;
    std::atomic<bool> valChanged;
    
    VTSlider mySlide;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
