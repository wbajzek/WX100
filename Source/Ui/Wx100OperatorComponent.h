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

#ifndef __JUCE_HEADER_536EF30C6152E846__
#define __JUCE_HEADER_536EF30C6152E846__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "Wx100Editor.h"
class Wx100AudioProcessor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Wx100OperatorComponent  : public Component,
                                public SliderListener,
                                public Timer
{
public:
    //==============================================================================
    Wx100OperatorComponent (String newName, int newOperatorNumber, Wx100AudioProcessor &newProcessor);
    ~Wx100OperatorComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Wx100AudioProcessor& processor;
    int operatorNumber = 0;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> groupComponent1;
    ScopedPointer<Slider> amp;
    ScopedPointer<Label> ampLabel;
    ScopedPointer<Label> ratioLabel;
    ScopedPointer<Slider> detune;
    ScopedPointer<Label> detuneLabel;
    ScopedPointer<Label> attackLabel;
    ScopedPointer<Slider> attack;
    ScopedPointer<Slider> decay;
    ScopedPointer<Label> decayLabel;
    ScopedPointer<Slider> sustain;
    ScopedPointer<Label> sustainLabel;
    ScopedPointer<Slider> release;
    ScopedPointer<Label> releaseLabel;
    ScopedPointer<Slider> phase;
    ScopedPointer<Label> phaseLabel;
    ScopedPointer<Wx100RatioSlider> ratio;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Wx100OperatorComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_536EF30C6152E846__
