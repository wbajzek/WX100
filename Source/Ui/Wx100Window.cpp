/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "Wx100Window.h"
#include "Wx100SynthEditor.h"
#include "Wx100AdvancedEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Wx100Window::Wx100Window (Wx100AudioProcessor &newProcessor)
    : AudioProcessorEditor(processor),
      processor(newProcessor)
{
    addAndMakeVisible (tabbedComponent = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedComponent->setTabBarDepth (31);
    tabbedComponent->addTab (TRANS("Synth"), Colours::lightgrey, new Wx100SynthEditor (newProcessor), true);
    tabbedComponent->addTab (TRANS("Settings"), Colours::lightgrey, new Wx100AdvancedEditor (newProcessor), true);
    tabbedComponent->setCurrentTabIndex (0);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 536);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Wx100Window::~Wx100Window()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    tabbedComponent = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Wx100Window::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Wx100Window::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    tabbedComponent->setBounds (0, 0, 800, 536);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Wx100Window" componentName=""
                 parentClasses="public AudioProcessorEditor" constructorParams="Wx100AudioProcessor &amp;newProcessor"
                 variableInitialisers="AudioProcessorEditor(processor),&#10;processor(newProcessor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="800" initialHeight="536">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TABBEDCOMPONENT name="new tabbed component" id="babfd188dad31636" memberName="tabbedComponent"
                   virtualName="" explicitFocusOrder="0" pos="0 0 800 536" orientation="top"
                   tabBarDepth="31" initialTab="0">
    <TAB name="Synth" colour="ffd3d3d3" useJucerComp="1" contentClassName=""
         constructorParams="newProcessor" jucerComponentFile="Wx100SynthEditor.cpp"/>
    <TAB name="Settings" colour="ffd3d3d3" useJucerComp="1" contentClassName=""
         constructorParams="newProcessor" jucerComponentFile="Wx100AdvancedEditor.cpp"/>
  </TABBEDCOMPONENT>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
