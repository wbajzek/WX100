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

#ifndef __JUCE_HEADER_37DF1175A92D0342__
#define __JUCE_HEADER_37DF1175A92D0342__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]

#include "Wx100OperatorComponent.h"
#include "Wx100FeedbackOperatorComponent.h"
#include "Wx100AlgorithmSelector.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Wx100SynthEditor  : public AudioProcessorEditor,
                          public Timer,
                          public SliderListener,
                          public ComboBoxListener
{
public:
    //==============================================================================
    Wx100SynthEditor (Wx100AudioProcessor& newProcessor);
    ~Wx100SynthEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Wx100AudioProcessor &processor;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> lfoGroupComponent;
    ScopedPointer<Slider> lfoFreq;
    ScopedPointer<Label> lfoFreqLabel;
    ScopedPointer<Label> lfoAmpModLabel;
    ScopedPointer<Slider> lfoAmpMod;
    ScopedPointer<Label> lfoPitchModLabel;
    ScopedPointer<Slider> lfoPitchWheel;
    ScopedPointer<Label> lfoInitPhaseLabel;
    ScopedPointer<Slider> lfoInitPhase;
    ScopedPointer<Label> lfoShapeLabel;
    ScopedPointer<Label> lfoSyncLabel;
    ScopedPointer<ComboBox> lfoShape;
    ScopedPointer<ComboBox> lfoSync;
    ScopedPointer<Wx100OperatorComponent> component2;
    ScopedPointer<Wx100OperatorComponent> component3;
    ScopedPointer<Wx100OperatorComponent> component4;
    ScopedPointer<Wx100FeedbackOperatorComponent> component;
    ScopedPointer<Wx100AlgorithmSelector> component5;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Wx100SynthEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_37DF1175A92D0342__
