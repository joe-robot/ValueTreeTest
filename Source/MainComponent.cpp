/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : getValButton("PrintVal"), myEditor("Blooooop"), mySlide(testTree)
{
    if(!loadXMLfromFile()) //If XML not loaded load inital values
    {
        static Identifier nodeType("NodeBode");
    
        ValueTree aTree(nodeType);
    
        testTree = aTree;
    
        static Identifier property("Double");
        testTree.setProperty(property, 55.55f, nullptr); //null ptr is the undo manager
    
        static Identifier property2("Text");
        testTree.setProperty(property2, "Hello", nullptr); //null ptr is the undo manager
        
        
        
    }
    
    static Identifier property("Text");
       
    
    myEditor.setText(testTree.getPropertyAsValue(property, nullptr).toString());
    getValButton.onClick = [this]{ exportValueTreeToXML();};
    addAndMakeVisible(&getValButton);
    
    
    myEditor.addListener(this);
    addAndMakeVisible(&myEditor);
    
    addAndMakeVisible(&mySlide);
    
    testTree.addListener(this);
    
    mySlide.updateSliderWithVT();
    
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
    
    
    //Use SliderVal Here
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    float width = getWidth();
    float height = getHeight();
    
    getValButton.setBounds(0, 0, width * 0.25f, height * 0.25f);
    
    
    myEditor.setBounds(0, 0.25f * height, width * 0.25f, height * 0.25f);
    
    mySlide.setBounds(0.25f * width, 0, 0.75f * width, 0.1f * height);

}

void MainComponent::getValueTreeVals()
{
    for(int i = 0; i < testTree.getNumProperties(); ++i)
    {
        var value = testTree.getProperty(testTree.getPropertyName(i));
        if(value.isDouble())
        {
            std::cout << "Is a double" << std::endl;
        }
        
        if(value.isInt())
        {
            std::cout << "Is Int" << std::endl;
        }
        
        if(value.isArray())
        {
            std::cout << "Is Array" << std::endl;
            
        }
        
        if(value.isBool())
        {
            std::cout << "Is Bool" << std::endl;
        }
        
        
        if(value.isString())
        {
            std::cout << "Is String" << std::endl;
        }
        std::cout << testTree.getPropertyName(i).toString() << " : " << testTree.getProperty(testTree.getPropertyName(i)).toString() << std::endl;
    }
}



void MainComponent::textEditorTextChanged(TextEditor &editor)
{
    std::cout << "Changed Text: " << editor.getText() << std::endl;
    static Identifier property("Text");
    testTree.setProperty(property, editor.getText(), nullptr); //null ptr is the undo manager
    
}

void MainComponent::exportValueTreeToXML()
{
    std::unique_ptr<XmlElement> vtXML = testTree.createXml();
    
    File writeTo(File::getCurrentWorkingDirectory()
    .getChildFile ("saveData.xml"));
    
    if(!(vtXML -> writeTo(writeTo)))
        DBG("FAIL");
    
}

bool MainComponent::loadXMLfromFile()
{
    File readFrom(File::getCurrentWorkingDirectory()
    .getChildFile ("saveData.xml"));
    
    
    if(readFrom.existsAsFile())
    {
        XmlDocument xmlDoc (readFrom);
        
        if (auto mainElement = xmlDoc.getDocumentElement())
        {
            testTree = testTree.fromXml(*mainElement);
            return true;
        }
        else
        {
            std::cout << "Failed to read XML: " << xmlDoc.getLastParseError() << std::endl;
        }
    }
    
    return false;
    
}


//Updating atomic with updated value tree (would need a sperate if statement for each property)
void MainComponent::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
    if(treeWhosePropertyHasChanged == testTree)
    {
        var treeVal = testTree.getProperty(property);
        
        if(treeVal.isDouble())
        {
            sliderVal = treeVal;
            std::cout << "slider val updated" << std::endl;
            //valChanged = true;
        }
    }
}
