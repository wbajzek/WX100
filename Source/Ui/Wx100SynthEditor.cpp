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
#include "Wx100.h"
#include "Wx100AudioProcessor.h"
//[/Headers]

#include "Wx100SynthEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Wx100SynthEditor::Wx100SynthEditor (Wx100AudioProcessor& newProcessor)
    : AudioProcessorEditor(newProcessor), processor(newProcessor)
{
    addAndMakeVisible (lfoGroupComponent = new GroupComponent ("lfoGroup",
                                                               TRANS("LFO")));
    lfoGroupComponent->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (lfoFreq = new Slider ("lfoFreq"));
    lfoFreq->setRange (0.01, 20, 0.01);
    lfoFreq->setSliderStyle (Slider::RotaryVerticalDrag);
    lfoFreq->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    lfoFreq->addListener (this);

    addAndMakeVisible (lfoFreqLabel = new Label ("lfoFreqLabel",
                                                 TRANS("Frequency")));
    lfoFreqLabel->setFont (Font (15.00f, Font::plain));
    lfoFreqLabel->setJustificationType (Justification::centred);
    lfoFreqLabel->setEditable (false, false, false);
    lfoFreqLabel->setColour (TextEditor::textColourId, Colours::black);
    lfoFreqLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lfoAmpModLabel = new Label ("lfoAmpModLabel",
                                                   TRANS("Amp Mod")));
    lfoAmpModLabel->setFont (Font (15.00f, Font::plain));
    lfoAmpModLabel->setJustificationType (Justification::centred);
    lfoAmpModLabel->setEditable (false, false, false);
    lfoAmpModLabel->setColour (TextEditor::textColourId, Colours::black);
    lfoAmpModLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lfoAmpMod = new Slider ("lfoAmpMod"));
    lfoAmpMod->setRange (0, 1, 0.01);
    lfoAmpMod->setSliderStyle (Slider::RotaryVerticalDrag);
    lfoAmpMod->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    lfoAmpMod->addListener (this);

    addAndMakeVisible (lfoPitchModLabel = new Label ("lfoPitchModLabel",
                                                     TRANS("Pitch Wheel")));
    lfoPitchModLabel->setFont (Font (15.00f, Font::plain));
    lfoPitchModLabel->setJustificationType (Justification::centred);
    lfoPitchModLabel->setEditable (false, false, false);
    lfoPitchModLabel->setColour (TextEditor::textColourId, Colours::black);
    lfoPitchModLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lfoPitchWheel = new Slider ("lfoPitchWheel"));
    lfoPitchWheel->setRange (0, 1, 0.01);
    lfoPitchWheel->setSliderStyle (Slider::RotaryVerticalDrag);
    lfoPitchWheel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    lfoPitchWheel->addListener (this);

    addAndMakeVisible (lfoInitPhaseLabel = new Label ("lfoInitPhaseLabel",
                                                      TRANS("Init Phase")));
    lfoInitPhaseLabel->setFont (Font (15.00f, Font::plain));
    lfoInitPhaseLabel->setJustificationType (Justification::centred);
    lfoInitPhaseLabel->setEditable (false, false, false);
    lfoInitPhaseLabel->setColour (TextEditor::textColourId, Colours::black);
    lfoInitPhaseLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lfoInitPhase = new Slider ("lfoInitPhase"));
    lfoInitPhase->setRange (0, 1, 0.001);
    lfoInitPhase->setSliderStyle (Slider::RotaryVerticalDrag);
    lfoInitPhase->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    lfoInitPhase->addListener (this);

    addAndMakeVisible (lfoShapeLabel = new Label ("lfoShapeLabel",
                                                  TRANS("Shape")));
    lfoShapeLabel->setFont (Font (15.00f, Font::plain));
    lfoShapeLabel->setJustificationType (Justification::centred);
    lfoShapeLabel->setEditable (false, false, false);
    lfoShapeLabel->setColour (TextEditor::textColourId, Colours::black);
    lfoShapeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lfoSyncLabel = new Label ("lfoSyncLabel",
                                                 TRANS("Sync")));
    lfoSyncLabel->setFont (Font (15.00f, Font::plain));
    lfoSyncLabel->setJustificationType (Justification::centred);
    lfoSyncLabel->setEditable (false, false, false);
    lfoSyncLabel->setColour (TextEditor::textColourId, Colours::black);
    lfoSyncLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lfoShape = new ComboBox ("lfoShape"));
    lfoShape->setEditableText (false);
    lfoShape->setJustificationType (Justification::centredLeft);
    lfoShape->setTextWhenNothingSelected (String::empty);
    lfoShape->setTextWhenNoChoicesAvailable (String::empty);
    lfoShape->addItem (TRANS("sine"), 1);
    lfoShape->addItem (TRANS("triangle"), 2);
    lfoShape->addItem (TRANS("saw"), 3);
    lfoShape->addItem (TRANS("ramp"), 4);
    lfoShape->addItem (TRANS("square"), 5);
    lfoShape->addItem (TRANS("noise"), 6);
    lfoShape->addListener (this);

    addAndMakeVisible (lfoSync = new ComboBox ("lfoShape"));
    lfoSync->setEditableText (false);
    lfoSync->setJustificationType (Justification::centredLeft);
    lfoSync->setTextWhenNothingSelected (String::empty);
    lfoSync->setTextWhenNoChoicesAvailable (String::empty);
    lfoSync->addItem (TRANS("Off"), 1);
    lfoSync->addItem (TRANS("On"), 2);
    lfoSync->addListener (this);

    addAndMakeVisible (component2 = new Wx100OperatorComponent ("Operator 1", 0, processor));
    addAndMakeVisible (component3 = new Wx100OperatorComponent ("Operator 2", 1, processor));
    addAndMakeVisible (component4 = new Wx100OperatorComponent ("Operator 3", 2, processor));
    addAndMakeVisible (component = new Wx100FeedbackOperatorComponent ("Operator 4", 3, processor));
    addAndMakeVisible (component5 = new Wx100AlgorithmSelector (processor));

    //[UserPreSize]
    //[/UserPreSize]

    setSize (912, 510);


    //[Constructor] You can add your own custom stuff here..
    lfoShape->setItemEnabled(0, false);
    lfoShape->addListener(this);
    lfoSync->setItemEnabled(0, false);
    lfoSync->addListener(this);
    processor.updateUi(true,true);
    timerCallback();
    startTimer(50);
    //[/Constructor]
}

Wx100SynthEditor::~Wx100SynthEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lfoGroupComponent = nullptr;
    lfoFreq = nullptr;
    lfoFreqLabel = nullptr;
    lfoAmpModLabel = nullptr;
    lfoAmpMod = nullptr;
    lfoPitchModLabel = nullptr;
    lfoPitchWheel = nullptr;
    lfoInitPhaseLabel = nullptr;
    lfoInitPhase = nullptr;
    lfoShapeLabel = nullptr;
    lfoSyncLabel = nullptr;
    lfoShape = nullptr;
    lfoSync = nullptr;
    component2 = nullptr;
    component3 = nullptr;
    component4 = nullptr;
    component = nullptr;
    component5 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Wx100SynthEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Wx100SynthEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    lfoGroupComponent->setBounds (792, 136, 88, 352);
    lfoFreq->setBounds (816, 184, 39, 24);
    lfoFreqLabel->setBounds (800, 160, 72, 24);
    lfoAmpModLabel->setBounds (800, 216, 72, 24);
    lfoAmpMod->setBounds (816, 240, 39, 24);
    lfoPitchModLabel->setBounds (800, 272, 72, 24);
    lfoPitchWheel->setBounds (816, 296, 39, 24);
    lfoInitPhaseLabel->setBounds (800, 328, 72, 24);
    lfoInitPhase->setBounds (816, 352, 39, 24);
    lfoShapeLabel->setBounds (800, 384, 72, 24);
    lfoSyncLabel->setBounds (800, 432, 72, 24);
    lfoShape->setBounds (808, 408, 56, 16);
    lfoSync->setBounds (808, 456, 56, 16);
    component2->setBounds (128, 376, 648, 112);
    component3->setBounds (128, 256, 648, 112);
    component4->setBounds (128, 136, 648, 112);
    component->setBounds (128, 16, 752, 112);
    component5->setBounds (8, 16, 112, 480);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Wx100SynthEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == lfoFreq)
    {
        //[UserSliderCode_lfoFreq] -- add your slider handling code here..
        processor.getFloatParam(LFO_FREQ)->updateProcessorAndHostFromUi(sliderThatWasMoved->getValue());
        //[/UserSliderCode_lfoFreq]
    }
    else if (sliderThatWasMoved == lfoAmpMod)
    {
        //[UserSliderCode_lfoAmpMod] -- add your slider handling code here..
        processor.getFloatParam(LFO_AMP_AMOUNT)->updateProcessorAndHostFromUi(sliderThatWasMoved->getValue());
        //[/UserSliderCode_lfoAmpMod]
    }
    else if (sliderThatWasMoved == lfoPitchWheel)
    {
        //[UserSliderCode_lfoPitchWheel] -- add your slider handling code here..
        processor.getFloatParam(LFO_PITCH_AMOUNT)->updateProcessorAndHostFromUi(sliderThatWasMoved->getValue());
        //[/UserSliderCode_lfoPitchWheel]
    }
    else if (sliderThatWasMoved == lfoInitPhase)
    {
        //[UserSliderCode_lfoInitPhase] -- add your slider handling code here..
        processor.getFloatParam(LFO_INIT_PHASE)->updateProcessorAndHostFromUi(sliderThatWasMoved->getValue());
        //[/UserSliderCode_lfoInitPhase]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void Wx100SynthEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == lfoShape)
    {
        //[UserComboBoxCode_lfoShape] -- add your combo box handling code here..
        processor.getIntParam(LFO_SHAPE)->updateProcessorAndHostFromUi(comboBoxThatHasChanged->getSelectedId() - 1);
        //[/UserComboBoxCode_lfoShape]
    }
    else if (comboBoxThatHasChanged == lfoSync)
    {
        //[UserComboBoxCode_lfoSync] -- add your combo box handling code here..
        //[/UserComboBoxCode_lfoSync]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void Wx100SynthEditor::timerCallback()
{
    FloatParam *param=processor.getFloatParam(LFO_FREQ);
    if (&lfoFreq && param->updateUiRequested()){
        lfoFreq->setValue (param->uiGet(), dontSendNotification);
    }
    param=processor.getFloatParam(LFO_AMP_AMOUNT);
    if (&lfoAmpMod && param->updateUiRequested()){
        lfoAmpMod->setValue (param->uiGet(), dontSendNotification);
    }
    param=processor.getFloatParam(LFO_PITCH_AMOUNT);
    if (&lfoPitchWheel && param->updateUiRequested()){
        lfoPitchWheel->setValue (param->uiGet(), dontSendNotification);
    }
    param=processor.getFloatParam(LFO_INIT_PHASE);
    if (&lfoInitPhase && param->updateUiRequested()){
        lfoInitPhase->setValue (param->uiGet(), dontSendNotification);
    }
    IntParam *intParam = processor.getIntParam(LFO_SHAPE);
    if (&lfoShape && intParam->updateUiRequested()){
        lfoShape->setSelectedId(intParam->uiGet() + 1, dontSendNotification);
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Wx100SynthEditor" componentName=""
                 parentClasses="public AudioProcessorEditor, public Timer" constructorParams="Wx100AudioProcessor&amp; newProcessor"
                 variableInitialisers="AudioProcessorEditor(newProcessor), processor(newProcessor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="912" initialHeight="510">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="lfoGroup" id="aba28bb1757b0546" memberName="lfoGroupComponent"
                  virtualName="" explicitFocusOrder="0" pos="792 136 88 352" title="LFO"
                  textpos="36"/>
  <SLIDER name="lfoFreq" id="c7a83db99a034b3f" memberName="lfoFreq" virtualName=""
          explicitFocusOrder="0" pos="816 184 39 24" min="0.010000000000000000208"
          max="20" int="0.010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="lfoFreqLabel" id="7da8785668a166a3" memberName="lfoFreqLabel"
         virtualName="" explicitFocusOrder="0" pos="800 160 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Frequency" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="lfoAmpModLabel" id="66021bf3a143f5a4" memberName="lfoAmpModLabel"
         virtualName="" explicitFocusOrder="0" pos="800 216 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Amp Mod" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="lfoAmpMod" id="255e38bf2c50137f" memberName="lfoAmpMod"
          virtualName="" explicitFocusOrder="0" pos="816 240 39 24" min="0"
          max="1" int="0.010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="lfoPitchModLabel" id="bf2fd785f5374a9e" memberName="lfoPitchModLabel"
         virtualName="" explicitFocusOrder="0" pos="800 272 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pitch Wheel" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="lfoPitchWheel" id="a3d7c10d9d07522a" memberName="lfoPitchWheel"
          virtualName="" explicitFocusOrder="0" pos="816 296 39 24" min="0"
          max="1" int="0.010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="lfoInitPhaseLabel" id="a932d7c20ebf90e3" memberName="lfoInitPhaseLabel"
         virtualName="" explicitFocusOrder="0" pos="800 328 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Init Phase" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="lfoInitPhase" id="381e7951cfb7933" memberName="lfoInitPhase"
          virtualName="" explicitFocusOrder="0" pos="816 352 39 24" min="0"
          max="1" int="0.0010000000000000000208" style="RotaryVerticalDrag"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="lfoShapeLabel" id="8a24102051de127f" memberName="lfoShapeLabel"
         virtualName="" explicitFocusOrder="0" pos="800 384 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Shape" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="lfoSyncLabel" id="6f8b2d0dcc1c43c0" memberName="lfoSyncLabel"
         virtualName="" explicitFocusOrder="0" pos="800 432 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sync" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <COMBOBOX name="lfoShape" id="51612512185d500b" memberName="lfoShape" virtualName=""
            explicitFocusOrder="0" pos="808 408 56 16" editable="0" layout="33"
            items="sine&#10;triangle&#10;saw&#10;ramp&#10;square&#10;noise"
            textWhenNonSelected="" textWhenNoItems=""/>
  <COMBOBOX name="lfoShape" id="e7048a05607d62e0" memberName="lfoSync" virtualName=""
            explicitFocusOrder="0" pos="808 456 56 16" editable="0" layout="33"
            items="Off&#10;On" textWhenNonSelected="" textWhenNoItems=""/>
  <JUCERCOMP name="" id="fc9691fa991bdf63" memberName="component2" virtualName=""
             explicitFocusOrder="0" pos="128 376 648 112" sourceFile="Wx100OperatorComponent.cpp"
             constructorParams="&quot;Operator 1&quot;, 0, processor"/>
  <JUCERCOMP name="" id="cb9132bba0bc64cf" memberName="component3" virtualName=""
             explicitFocusOrder="0" pos="128 256 648 112" sourceFile="Wx100OperatorComponent.cpp"
             constructorParams="&quot;Operator 2&quot;, 1, processor"/>
  <JUCERCOMP name="" id="e5aca3bd16fb9e2" memberName="component4" virtualName=""
             explicitFocusOrder="0" pos="128 136 648 112" sourceFile="Wx100OperatorComponent.cpp"
             constructorParams="&quot;Operator 3&quot;, 2, processor"/>
  <JUCERCOMP name="" id="88186d646a5d2007" memberName="component" virtualName=""
             explicitFocusOrder="0" pos="128 16 752 112" sourceFile="Wx100FeedbackOperatorComponent.cpp"
             constructorParams="&quot;Operator 4&quot;, 3, processor"/>
  <JUCERCOMP name="" id="1f2c10ddb5238693" memberName="component5" virtualName=""
             explicitFocusOrder="0" pos="8 16 112 480" sourceFile="Wx100AlgorithmSelector.cpp"
             constructorParams="processor"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
