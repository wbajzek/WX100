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

#include "Wx100FeedbackOperatorComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Wx100FeedbackOperatorComponent::Wx100FeedbackOperatorComponent (String newName, int newOperatorNumber, Wx100AudioProcessor &newProcessor)
    : processor(newProcessor), operatorNumber(newOperatorNumber)
{
    addAndMakeVisible (groupComponent = new GroupComponent ("operatorGroup",
                                                            TRANS("Operator")));

    addAndMakeVisible (amp = new Slider ("amp"));
    amp->setRange (0, 1, 0.01);
    amp->setSliderStyle (Slider::RotaryVerticalDrag);
    amp->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    amp->addListener (this);

    addAndMakeVisible (ampLabel = new Label ("ampLabel",
                                             TRANS("Amp\n")));
    ampLabel->setFont (Font (15.00f, Font::plain));
    ampLabel->setJustificationType (Justification::centred);
    ampLabel->setEditable (false, false, false);
    ampLabel->setColour (TextEditor::textColourId, Colours::black);
    ampLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (ratio = new Wx100RatioSlider ("ratio"));
    ratio->setRange (0.25, 25.95, 0.01);
    ratio->setSliderStyle (Slider::RotaryVerticalDrag);
    ratio->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    ratio->addListener (this);

    addAndMakeVisible (ratioLabel = new Label ("ratioLabel",
                                               TRANS("Ratio")));
    ratioLabel->setFont (Font (15.00f, Font::plain));
    ratioLabel->setJustificationType (Justification::centred);
    ratioLabel->setEditable (false, false, false);
    ratioLabel->setColour (TextEditor::textColourId, Colours::black);
    ratioLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (detune = new Slider ("detune"));
    detune->setRange (-1, 1, 0.01);
    detune->setSliderStyle (Slider::RotaryVerticalDrag);
    detune->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    detune->addListener (this);

    addAndMakeVisible (detuneLabel = new Label ("detuneLabel",
                                                TRANS("Detune")));
    detuneLabel->setFont (Font (15.00f, Font::plain));
    detuneLabel->setJustificationType (Justification::centred);
    detuneLabel->setEditable (false, false, false);
    detuneLabel->setColour (TextEditor::textColourId, Colours::black);
    detuneLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (attackLabel = new Label ("attackLabel",
                                                TRANS("Attack")));
    attackLabel->setFont (Font (15.00f, Font::plain));
    attackLabel->setJustificationType (Justification::centred);
    attackLabel->setEditable (false, false, false);
    attackLabel->setColour (TextEditor::textColourId, Colours::black);
    attackLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (attack = new Slider ("attack"));
    attack->setRange (0, 20, 0.001);
    attack->setSliderStyle (Slider::RotaryVerticalDrag);
    attack->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    attack->addListener (this);

    addAndMakeVisible (decay = new Slider ("decay"));
    decay->setRange (0.001, 20, 0.001);
    decay->setSliderStyle (Slider::RotaryVerticalDrag);
    decay->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    decay->addListener (this);

    addAndMakeVisible (decayLabel = new Label ("decayLabel",
                                               TRANS("Decay\n")));
    decayLabel->setFont (Font (15.00f, Font::plain));
    decayLabel->setJustificationType (Justification::centred);
    decayLabel->setEditable (false, false, false);
    decayLabel->setColour (TextEditor::textColourId, Colours::black);
    decayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sustain = new Slider ("sustain"));
    sustain->setRange (0, 1, 0.001);
    sustain->setSliderStyle (Slider::RotaryVerticalDrag);
    sustain->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sustain->addListener (this);

    addAndMakeVisible (sustainLabel = new Label ("sustainLabel",
                                                 TRANS("Sustain")));
    sustainLabel->setFont (Font (15.00f, Font::plain));
    sustainLabel->setJustificationType (Justification::centred);
    sustainLabel->setEditable (false, false, false);
    sustainLabel->setColour (TextEditor::textColourId, Colours::black);
    sustainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (release = new Slider ("release"));
    release->setRange (0.001, 20, 0.001);
    release->setSliderStyle (Slider::RotaryVerticalDrag);
    release->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    release->addListener (this);

    addAndMakeVisible (releaseLabel = new Label ("releaseLabel",
                                                 TRANS("Release")));
    releaseLabel->setFont (Font (15.00f, Font::plain));
    releaseLabel->setJustificationType (Justification::centred);
    releaseLabel->setEditable (false, false, false);
    releaseLabel->setColour (TextEditor::textColourId, Colours::black);
    releaseLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (phase = new Slider ("phase"));
    phase->setRange (0, 1, 0.001);
    phase->setSliderStyle (Slider::RotaryVerticalDrag);
    phase->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    phase->addListener (this);

    addAndMakeVisible (phaseLabel = new Label ("phaseLabel",
                                               TRANS("Phase")));
    phaseLabel->setFont (Font (15.00f, Font::plain));
    phaseLabel->setJustificationType (Justification::centred);
    phaseLabel->setEditable (false, false, false);
    phaseLabel->setColour (TextEditor::textColourId, Colours::black);
    phaseLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (feedback = new Slider ("feedback"));
    feedback->setRange (0, 1, 0.01);
    feedback->setSliderStyle (Slider::RotaryVerticalDrag);
    feedback->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    feedback->addListener (this);

    addAndMakeVisible (feedbackLabel = new Label ("feedbackLabel",
                                                  TRANS("Feedback")));
    feedbackLabel->setFont (Font (15.00f, Font::plain));
    feedbackLabel->setJustificationType (Justification::centred);
    feedbackLabel->setEditable (false, false, false);
    feedbackLabel->setColour (TextEditor::textColourId, Colours::black);
    feedbackLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lfoAmp = new Slider ("ampLfo"));
    lfoAmp->setRange (0, 1, 0.001);
    lfoAmp->setSliderStyle (Slider::RotaryVerticalDrag);
    lfoAmp->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    lfoAmp->addListener (this);

    addAndMakeVisible (lfoAmpLabel = new Label ("lfoAmpLabel",
                                                TRANS("Amp LFO")));
    lfoAmpLabel->setFont (Font (15.00f, Font::plain));
    lfoAmpLabel->setJustificationType (Justification::centred);
    lfoAmpLabel->setEditable (false, false, false);
    lfoAmpLabel->setColour (TextEditor::textColourId, Colours::black);
    lfoAmpLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (756, 112);


    //[Constructor] You can add your own custom stuff here..
    amp->setScrollWheelEnabled(false);
    ratio->setScrollWheelEnabled(false);
    detune->setScrollWheelEnabled(false);
    phase->setScrollWheelEnabled(false);
    attack->setScrollWheelEnabled(false);
    decay->setScrollWheelEnabled(false);
    sustain->setScrollWheelEnabled(false);
    release->setScrollWheelEnabled(false);
    lfoAmp->setScrollWheelEnabled(false);
    feedback->setScrollWheelEnabled(false);
    groupComponent->setText("");
    processor.updateUi(true,true);
    timerCallback();
    startTimer(50);
    //[/Constructor]
}

Wx100FeedbackOperatorComponent::~Wx100FeedbackOperatorComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent = nullptr;
    amp = nullptr;
    ampLabel = nullptr;
    ratio = nullptr;
    ratioLabel = nullptr;
    detune = nullptr;
    detuneLabel = nullptr;
    attackLabel = nullptr;
    attack = nullptr;
    decay = nullptr;
    decayLabel = nullptr;
    sustain = nullptr;
    sustainLabel = nullptr;
    release = nullptr;
    releaseLabel = nullptr;
    phase = nullptr;
    phaseLabel = nullptr;
    feedback = nullptr;
    feedbackLabel = nullptr;
    lfoAmp = nullptr;
    lfoAmpLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Wx100FeedbackOperatorComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Wx100FeedbackOperatorComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    groupComponent->setBounds (0, 0, 752, 112);
    amp->setBounds (24, 40, 39, 56);
    ampLabel->setBounds (16, 16, 56, 24);
    ratio->setBounds (80, 40, 40, 56);
    ratioLabel->setBounds (72, 16, 56, 24);
    detune->setBounds (136, 40, 40, 56);
    detuneLabel->setBounds (128, 16, 56, 24);
    attackLabel->setBounds (288, 16, 56, 24);
    attack->setBounds (296, 40, 40, 56);
    decay->setBounds (360, 40, 40, 56);
    decayLabel->setBounds (352, 16, 56, 24);
    sustain->setBounds (424, 40, 40, 56);
    sustainLabel->setBounds (416, 16, 56, 24);
    release->setBounds (488, 40, 40, 56);
    releaseLabel->setBounds (480, 16, 56, 24);
    phase->setBounds (200, 40, 40, 56);
    phaseLabel->setBounds (192, 16, 56, 24);
    feedback->setBounds (680, 40, 40, 56);
    feedbackLabel->setBounds (664, 16, 72, 24);
    lfoAmp->setBounds (584, 40, 40, 56);
    lfoAmpLabel->setBounds (576, 16, 56, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Wx100FeedbackOperatorComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == amp)
    {
        //[UserSliderCode_amp] -- add your slider handling code here..
        processor.getFloatParam(AMP_0 + operatorNumber)->updateProcessorAndHostFromUi(sliderThatWasMoved->getValue());
        //[/UserSliderCode_amp]
    }
    else if (sliderThatWasMoved == ratio)
    {
        //[UserSliderCode_ratio] -- add your slider handling code here..
        processor.getFloatParam(RATIO_0 + operatorNumber)->updateProcessorAndHostFromUi(sliderThatWasMoved->getValue());
        //[/UserSliderCode_ratio]
    }
    else if (sliderThatWasMoved == detune)
    {
        //[UserSliderCode_detune] -- add your slider handling code here..
        processor.getFloatParam(TUNING_0 + operatorNumber)->updateProcessorAndHostFromUi(sliderThatWasMoved->getValue());
        //[/UserSliderCode_detune]
    }
    else if (sliderThatWasMoved == attack)
    {
        //[UserSliderCode_attack] -- add your slider handling code here..
        processor.getFloatParam(ATTACK_0 + operatorNumber)->updateProcessorAndHostFromUi(sliderThatWasMoved->getValue());
        //[/UserSliderCode_attack]
    }
    else if (sliderThatWasMoved == decay)
    {
        //[UserSliderCode_decay] -- add your slider handling code here..
        processor.getFloatParam(DECAY_0 + operatorNumber)->updateProcessorAndHostFromUi(sliderThatWasMoved->getValue());
        //[/UserSliderCode_decay]
    }
    else if (sliderThatWasMoved == sustain)
    {
        //[UserSliderCode_sustain] -- add your slider handling code here..
        processor.getFloatParam(SUSTAIN_0 + operatorNumber)->updateProcessorAndHostFromUi(sliderThatWasMoved->getValue());
        //[/UserSliderCode_sustain]
    }
    else if (sliderThatWasMoved == release)
    {
        //[UserSliderCode_release] -- add your slider handling code here..
        processor.getFloatParam(RELEASE_0 + operatorNumber)->updateProcessorAndHostFromUi(sliderThatWasMoved->getValue());
        //[/UserSliderCode_release]
    }
    else if (sliderThatWasMoved == phase)
    {
        //[UserSliderCode_phase] -- add your slider handling code here..
        processor.getFloatParam(PHASE_0 + operatorNumber)->updateProcessorAndHostFromUi(sliderThatWasMoved->getValue());
        //[/UserSliderCode_phase]
    }
    else if (sliderThatWasMoved == feedback)
    {
        //[UserSliderCode_feedback] -- add your slider handling code here..
        // only one with feedback
        processor.getFloatParam(FEEDBACK_3)->updateProcessorAndHostFromUi(sliderThatWasMoved->getValue());
        //[/UserSliderCode_feedback]
    }
    else if (sliderThatWasMoved == lfoAmp)
    {
        //[UserSliderCode_lfoAmp] -- add your slider handling code here..
        processor.getFloatParam(LFO_AMP_0 + operatorNumber)->updateProcessorAndHostFromUi(sliderThatWasMoved->getValue());
        //[/UserSliderCode_lfoAmp]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void Wx100FeedbackOperatorComponent::timerCallback()
{
    FloatParam *param = processor.getFloatParam(AMP_0 + operatorNumber);
    if (&amp && param->updateUiRequested()){
        amp->setValue (param->uiGet(), dontSendNotification);
    }
    param = processor.getFloatParam(TUNING_0 + operatorNumber);
    if (&detune && param->updateUiRequested()){
        detune->setValue (param->uiGet(), dontSendNotification);
    }
    param = processor.getFloatParam(ATTACK_0 + operatorNumber);
    if (&attack && param->updateUiRequested()){
        attack->setValue (param->uiGet(), dontSendNotification);
    }
    param = processor.getFloatParam(DECAY_0 + operatorNumber);
    if (&decay && param->updateUiRequested()){
        decay->setValue (param->uiGet(), dontSendNotification);
    }
    param = processor.getFloatParam(SUSTAIN_0 + operatorNumber);
    if (&sustain && param->updateUiRequested()){
        sustain->setValue (param->uiGet(), dontSendNotification);
    }
    param = processor.getFloatParam(RELEASE_0 + operatorNumber);
    if (&release && param->updateUiRequested()){
        release->setValue (param->uiGet(), dontSendNotification);
    }
    param = processor.getFloatParam(PHASE_0 + operatorNumber);
    if (&phase && param->updateUiRequested()){
        phase->setValue (param->uiGet(), dontSendNotification);
    }
    param = processor.getFloatParam(RATIO_0 + operatorNumber);
    if (&ratio && param->updateUiRequested()){
        ratio->setValue (param->uiGet(), dontSendNotification);
    }
    param = processor.getFloatParam(LFO_AMP_0 + operatorNumber);
    if (&lfoAmp && param->updateUiRequested()){
        lfoAmp->setValue (param->uiGet(), dontSendNotification);
    }
    param = processor.getFloatParam(FEEDBACK_3);
    if (&feedback && param->updateUiRequested()){
        feedback->setValue (param->uiGet(), dontSendNotification);
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Wx100FeedbackOperatorComponent"
                 componentName="" parentClasses="public Component, public SliderListener, public Timer"
                 constructorParams="String newName, int newOperatorNumber, Wx100AudioProcessor &amp;newProcessor"
                 variableInitialisers="processor(newProcessor), operatorNumber(newOperatorNumber)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="756" initialHeight="112">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="operatorGroup" id="508e4f8731ff05d0" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="0 0 752 112" title="Operator"/>
  <SLIDER name="amp" id="ce6c74e2b835cdf7" memberName="amp" virtualName=""
          explicitFocusOrder="0" pos="24 40 39 56" min="0" max="1" int="0.010000000000000000208"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="ampLabel" id="eba77c8120b80f1c" memberName="ampLabel" virtualName=""
         explicitFocusOrder="0" pos="16 16 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Amp&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="ratio" id="53ae365e9f93b88f" memberName="ratio" virtualName="Wx100RatioSlider"
          explicitFocusOrder="0" pos="80 40 40 56" min="0.25" max="25.949999999999999289"
          int="0.010000000000000000208" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="ratioLabel" id="79bdfbd630590cc0" memberName="ratioLabel"
         virtualName="" explicitFocusOrder="0" pos="72 16 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Ratio" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="detune" id="455e6269f7ade9db" memberName="detune" virtualName=""
          explicitFocusOrder="0" pos="136 40 40 56" min="-1" max="1" int="0.010000000000000000208"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="detuneLabel" id="8f25b61b08c86300" memberName="detuneLabel"
         virtualName="" explicitFocusOrder="0" pos="128 16 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Detune" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="attackLabel" id="fd65b26aa809484e" memberName="attackLabel"
         virtualName="" explicitFocusOrder="0" pos="288 16 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Attack" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="attack" id="285920f3139a4dde" memberName="attack" virtualName=""
          explicitFocusOrder="0" pos="296 40 40 56" min="0" max="20" int="0.0010000000000000000208"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="decay" id="e884465479df73d" memberName="decay" virtualName=""
          explicitFocusOrder="0" pos="360 40 40 56" min="0.0010000000000000000208"
          max="20" int="0.0010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="decayLabel" id="26023aad35b5fc30" memberName="decayLabel"
         virtualName="" explicitFocusOrder="0" pos="352 16 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Decay&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="sustain" id="dbf7ff85a99e1cc1" memberName="sustain" virtualName=""
          explicitFocusOrder="0" pos="424 40 40 56" min="0" max="1" int="0.0010000000000000000208"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="sustainLabel" id="830600c9d8619ddb" memberName="sustainLabel"
         virtualName="" explicitFocusOrder="0" pos="416 16 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sustain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="release" id="7829583fef75bd12" memberName="release" virtualName=""
          explicitFocusOrder="0" pos="488 40 40 56" min="0.0010000000000000000208"
          max="20" int="0.0010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="releaseLabel" id="e6f24aba9944a141" memberName="releaseLabel"
         virtualName="" explicitFocusOrder="0" pos="480 16 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Release" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="phase" id="d7edb2b76b9c771c" memberName="phase" virtualName=""
          explicitFocusOrder="0" pos="200 40 40 56" min="0" max="1" int="0.0010000000000000000208"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="phaseLabel" id="d9280ced4b4bd3f7" memberName="phaseLabel"
         virtualName="" explicitFocusOrder="0" pos="192 16 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Phase" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="feedback" id="110efb4dd567415" memberName="feedback" virtualName=""
          explicitFocusOrder="0" pos="680 40 40 56" min="0" max="1" int="0.010000000000000000208"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="feedbackLabel" id="7be64f4c15964aaf" memberName="feedbackLabel"
         virtualName="" explicitFocusOrder="0" pos="664 16 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Feedback" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="ampLfo" id="bb185b2b29399f58" memberName="lfoAmp" virtualName=""
          explicitFocusOrder="0" pos="584 40 40 56" min="0" max="1" int="0.0010000000000000000208"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="lfoAmpLabel" id="70ede97c75029075" memberName="lfoAmpLabel"
         virtualName="" explicitFocusOrder="0" pos="576 16 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Amp LFO" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
