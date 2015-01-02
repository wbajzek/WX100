/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "Wx100AudioProcessor.h"
#include "Wx100Editor.h"
#include "Wx100TuningEditor.h"


//==============================================================================
Wx100AudioProcessorEditor::Wx100AudioProcessorEditor (Wx100AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), tuningEditor(this)
{

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    setSize (590, 415);
    for (int i = 0; i < numOperators; ++i)
    {
        addAndMakeVisible(operators[i]);
        
        amp[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        amp[i].setSize(50, 50);
        amp[i].setRange(0.0, 1.0, 0.001);
        amp[i].setScrollWheelEnabled(false);
        amp[i].setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
        amp[i].addListener(this);
        addAndMakeVisible(amp[i]);

        ratio[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        ratio[i].setSize(50, 50);
        ratio[i].setRange(ratios[0], ratios[numRatios - 1], 0.01);
        ratio[i].setScrollWheelEnabled(false);
        ratio[i].setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
        ratio[i].addListener(this);
        addAndMakeVisible(ratio[i]);

        tuning[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        tuning[i].setSize(50, 50);
        tuning[i].setRange(-1.0, 1.0, 0.001);
        tuning[i].setScrollWheelEnabled(false);
        tuning[i].setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
        tuning[i].addListener(this);
        addAndMakeVisible(tuning[i]);

        attack[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        attack[i].setSize(50, 50);
        attack[i].setRange(0.0, 20.0, 0.001);
        attack[i].setScrollWheelEnabled(false);
        attack[i].setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
        attack[i].addListener(this);
        addAndMakeVisible(attack[i]);

        decay[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        decay[i].setSize(50, 50);
        decay[i].setRange(0.001, 20.0, 0.001);
        decay[i].setScrollWheelEnabled(false);
        decay[i].setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
        decay[i].addListener(this);
        addAndMakeVisible(decay[i]);

        sustain[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        sustain[i].setSize(50, 50);
        sustain[i].setRange(0.0, 1.0, 0.001);
        sustain[i].setScrollWheelEnabled(false);
        sustain[i].setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
        sustain[i].addListener(this);
        addAndMakeVisible(sustain[i]);

        release[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        release[i].setSize(50, 50);
        release[i].setRange(0.001, 20.0, 0.001);
        release[i].setScrollWheelEnabled(false);
        release[i].setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
        release[i].addListener(this);
        addAndMakeVisible(release[i]);

        phase[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        phase[i].setSize(50, 50);
        phase[i].setRange(0.0, 1.0, 0.0001);
        phase[i].setScrollWheelEnabled(false);
        phase[i].setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
        phase[i].addListener(this);
        addAndMakeVisible(phase[i]);
    }
    
    feedback.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    feedback.setSize(50, 50);
    feedback.setRange(0.0, 1.0, 0.001);
    feedback.setScrollWheelEnabled(false);
    feedback.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    feedback.addListener(this);
    addAndMakeVisible(feedback);

    algorithm.addItem("1",1);
    algorithm.addItem("2",2);
    algorithm.addItem("3",3);
    algorithm.addItem("4",4);
    algorithm.addItem("5",5);
    algorithm.addItem("6",6);
    algorithm.addItem("7",7);
    algorithm.addItem("8",8);
    algorithm.setWantsKeyboardFocus(false);
    algorithm.setItemEnabled(0, false);
    algorithm.setEditableText(false);
    algorithm.setScrollWheelEnabled(false);
    algorithm.addListener(this);
    addAndMakeVisible(algorithm);
    
    scale.setButtonText("Scale Editor");
    scale.addListener(this);
    addAndMakeVisible(scale);
    
    scaleRoot.addItem("C",1);
    scaleRoot.addItem("C#",2);
    scaleRoot.addItem("D",3);
    scaleRoot.addItem("D#",4);
    scaleRoot.addItem("E",5);
    scaleRoot.addItem("F",6);
    scaleRoot.addItem("F#",7);
    scaleRoot.addItem("G",8);
    scaleRoot.addItem("G#",9);
    scaleRoot.addItem("A",10);
    scaleRoot.addItem("A#",11);
    scaleRoot.addItem("B",12);
    scaleRoot.setWantsKeyboardFocus(false);
    scaleRoot.setItemEnabled(0, false);
    scaleRoot.setEditableText(false);
    scaleRoot.setScrollWheelEnabled(false);
    scaleRoot.addListener(this);
    addAndMakeVisible(scaleRoot);
    
    lfoFrequency.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    lfoFrequency.setRange(0.01, 100.0, 0.01);
    lfoFrequency.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    lfoFrequency.setPopupDisplayEnabled(true, this);
    lfoFrequency.setScrollWheelEnabled(false);
    lfoFrequency.addListener(this);
    addAndMakeVisible(lfoFrequency);
    
    lfoShape.addItem("Sine",SINE_WAVE_TABLE + 1);
    lfoShape.addItem("Triangle",TRIANGLE_WAVE_TABLE + 1);
    lfoShape.addItem("Saw",SAW_WAVE_TABLE + 1);
    lfoShape.addItem("Ramp",RAMP_WAVE_TABLE + 1);
    lfoShape.setWantsKeyboardFocus(false);
    lfoShape.setItemEnabled(0, false);
    lfoShape.setEditableText(false);
    lfoShape.setScrollWheelEnabled(false);
    lfoShape.addListener(this);
    addAndMakeVisible(lfoShape);
    
    lfoAmpAmount.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    lfoAmpAmount.setRange(0.0, 1.0, 0.01);
    lfoAmpAmount.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    lfoAmpAmount.setPopupDisplayEnabled(true, this);
    lfoAmpAmount.setScrollWheelEnabled(false);
    lfoAmpAmount.addListener(this);
    addAndMakeVisible(lfoAmpAmount);
    
    lfoPitchAmount.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    lfoPitchAmount.setRange(0.0, 1.0, 0.01);
    lfoPitchAmount.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    lfoPitchAmount.setPopupDisplayEnabled(true, this);
    lfoPitchAmount.setScrollWheelEnabled(false);
    lfoPitchAmount.addListener(this);
    addAndMakeVisible(lfoPitchAmount);
    
    lfoInitPhase.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    lfoInitPhase.setRange(0.0, 1.0, 0.01);
    lfoInitPhase.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    lfoInitPhase.setPopupDisplayEnabled(true, this);
    lfoInitPhase.setScrollWheelEnabled(false);
    lfoInitPhase.addListener(this);
    addAndMakeVisible(lfoInitPhase);

    processor.updateUi(true,true);
    timerCallback();
    startTimer(50);
}

Wx100AudioProcessorEditor::~Wx100AudioProcessorEditor()
{
}

//==============================================================================
void Wx100AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    
    int left = 20;
    int top = 0;
    int bottomRow = top + 345;
    g.drawFittedText ("Amp", left, top, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Ratio", left + 60, top, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Detune", left + 120, top, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Attack", left + 180, top, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Decay", left + 240, top, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Sustain", left + 300, top, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Release", left + 360, top, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Phase", left + 420, top, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Fdbk", left + 480, top + 240, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Algorithm", left, bottomRow, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Scale", left + 60, bottomRow, 140, 25, Justification::centred, 1);
    g.drawFittedText ("Scale Root", left + 220, bottomRow, 50, 25, Justification::centred, 1);
    g.drawFittedText ("LFO Freq", left + 280, bottomRow, 60, 25, Justification::centred, 1);
    g.drawFittedText ("Shape", left + 345, bottomRow, 90, 25, Justification::centred, 1);
    g.drawFittedText ("Amp", left + 430, bottomRow, 60, 25, Justification::centred, 1);
    g.drawFittedText ("Pitch", left + 470, bottomRow, 60, 25, Justification::centred, 1);
    g.drawFittedText ("Phase", left + 510, bottomRow, 60, 25, Justification::centred, 1);
}

void Wx100AudioProcessorEditor::resized()
{
    int left = 20;
    int top = 40;
    int bottomRow = top + 335;
    for (int i = 0; i < numOperators; ++i) {
        operators[i].setBounds (left - 10, top + (80 * i) - 20, 490, 80);
        amp[i].setBounds (left, top + (80 * i), 20, 20);
        ratio[i].setBounds (left + 60, top + (80 * i), 20, 20);
        tuning[i].setBounds (left + 120, top + (80 * i), 20, 20);
        attack[i].setBounds (left + 180, top + (80 * i), 20, 20);
        decay[i].setBounds (left + 240, top + (80 * i), 20, 20);
        sustain[i].setBounds (left + 300, top + (80 * i), 20, 20);
        release[i].setBounds (left + 360, top + (80 * i), 20, 20);
        phase[i].setBounds (left + 420, top + (80 * i), 20, 20);
    }
    operators[3].setBounds (left - 10, top + 220, 550, 80);
    feedback.setBounds(left + 480, top + 240, 20, 20);
    algorithm.setBounds(left, bottomRow, 50, 20);
    scale.setBounds (left + 60, bottomRow, 140, 20);
    scaleRoot.setBounds (left + 220, bottomRow, 50, 20);
    lfoFrequency.setBounds (left + 280, bottomRow, 60, 20);
    lfoShape.setBounds (left + 345, bottomRow, 90, 20);
    lfoAmpAmount.setBounds (left + 430, bottomRow, 60, 20);
    lfoPitchAmount.setBounds (left + 470, bottomRow, 60, 20);
    lfoInitPhase.setBounds (left + 510, bottomRow, 60, 20);
}

void Wx100AudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    for (int i = 0; i < numOperators; ++i) {
        if (slider == &amp[i])
            processor.getFloatParam(AMP_0 + i)->updateProcessorAndHostFromUi(slider->getValue());
        if (slider == &ratio[i])
            processor.getFloatParam(RATIO_0 + i)->updateProcessorAndHostFromUi(slider->getValue());
        if (slider == &tuning[i])
            processor.getFloatParam(TUNING_0 + i)->updateProcessorAndHostFromUi(slider->getValue());
        if (slider == &attack[i])
            processor.getFloatParam(ATTACK_0 + i)->updateProcessorAndHostFromUi(slider->getValue());
        if (slider == &decay[i])
            processor.getFloatParam(DECAY_0 + i)->updateProcessorAndHostFromUi(slider->getValue());
        if (slider == &sustain[i])
            processor.getFloatParam(SUSTAIN_0 + i)->updateProcessorAndHostFromUi(slider->getValue());
        if (slider == &release[i])
            processor.getFloatParam(RELEASE_0 + i)->updateProcessorAndHostFromUi(slider->getValue());
        if (slider == &phase[i])
            processor.getFloatParam(PHASE_0 + i)->updateProcessorAndHostFromUi(slider->getValue());
    }
    if (slider == &feedback)
        processor.getFloatParam(FEEDBACK_3)->updateProcessorAndHostFromUi(slider->getValue());
    if (slider == &lfoFrequency)
        processor.getFloatParam(LFO_FREQ)->updateProcessorAndHostFromUi(slider->getValue());
    if (slider == &lfoAmpAmount)
        processor.getFloatParam(LFO_AMP_AMOUNT)->updateProcessorAndHostFromUi(slider->getValue());
    if (slider == &lfoPitchAmount)
        processor.getFloatParam(LFO_PITCH_AMOUNT)->updateProcessorAndHostFromUi(slider->getValue());
    if (slider == &lfoInitPhase)
        processor.getFloatParam(LFO_INIT_PHASE)->updateProcessorAndHostFromUi(slider->getValue());
}

void Wx100AudioProcessorEditor::comboBoxChanged (ComboBox* comboBox)
{
    if (comboBox == &algorithm)
        processor.getIntParam(ALGORITHM)->updateProcessorAndHostFromUi(comboBox->getSelectedId());
    if (comboBox == &scaleRoot)
        processor.getIntParam(SCALE_ROOT)->updateProcessorAndHostFromUi(comboBox->getSelectedId());
    if (comboBox == &lfoShape)
        processor.getIntParam(LFO_SHAPE)->updateProcessorAndHostFromUi(comboBox->getSelectedId() - 1);
}

void Wx100AudioProcessorEditor::buttonClicked(Button* button)
{
    if (button == &scale)
        DialogWindow::showDialog("Scala File", &tuningEditor, &tuningEditor, Colours::white, true);
}


/** Called when the user changes the text in some way. */
void Wx100AudioProcessorEditor::textEditorTextChanged (TextEditor& editor)
{
    processor.getStringParam(SCALE)->updateProcessorAndHostFromUi(editor.getText());
}

/** Called when the user presses the return key. */
void Wx100AudioProcessorEditor::textEditorReturnKeyPressed (TextEditor& editor)
{
    processor.getStringParam(SCALE)->updateProcessorAndHostFromUi(editor.getText());
}

/** Called when the user presses the escape key. */
void Wx100AudioProcessorEditor::textEditorEscapeKeyPressed (TextEditor& editor)
{
    processor.getStringParam(SCALE)->updateProcessorAndHostFromUi(editor.getText());
}

/** Called when the text editor loses focus. */
void Wx100AudioProcessorEditor::textEditorFocusLost (TextEditor& editor)
{
    processor.getStringParam(SCALE)->updateProcessorAndHostFromUi(editor.getText());
}

void Wx100AudioProcessorEditor::timerCallback()
{
    for (int i = 0; i < numOperators; ++i)
    {
        FloatParam *param=processor.getFloatParam(AMP_0 + i);
        if (&amp[i] && param->updateUiRequested()){
            amp[i].setValue (param->uiGet(), dontSendNotification);
        }
        param=processor.getFloatParam(RATIO_0 + i);
        if (&ratio[i] && param->updateUiRequested()){
            ratio[i].setValue (param->uiGet(), dontSendNotification);
        }
        param=processor.getFloatParam(TUNING_0 + i);
        if (&tuning[i] && param->updateUiRequested()){
            tuning[i].setValue (param->uiGet(), dontSendNotification);
        }
        param=processor.getFloatParam(ATTACK_0 + i);
        if (&attack[i] && param->updateUiRequested()){
            attack[i].setValue (param->uiGet(), dontSendNotification);
        }
        param=processor.getFloatParam(DECAY_0 + i);
        if (&decay[i] && param->updateUiRequested()){
            decay[i].setValue (param->uiGet(), dontSendNotification);
        }
        param=processor.getFloatParam(SUSTAIN_0 + i);
        if (&sustain[i] && param->updateUiRequested()){
            sustain[i].setValue (param->uiGet(), dontSendNotification);
        }
        param=processor.getFloatParam(RELEASE_0 + i);
        if (&release[i] && param->updateUiRequested()){
            release[i].setValue (param->uiGet(), dontSendNotification);
        }
        param=processor.getFloatParam(PHASE_0 + i);
        if (&phase[i] && param->updateUiRequested()){
            phase[i].setValue (param->uiGet(), dontSendNotification);
        }
    }
    FloatParam *param=processor.getFloatParam(FEEDBACK_3);
    if (&feedback && param->updateUiRequested()){
        feedback.setValue (param->uiGet(), dontSendNotification);
    }
    param=processor.getFloatParam(LFO_FREQ);
    if (&lfoFrequency && param->updateUiRequested()){
        lfoFrequency.setValue (param->uiGet(), dontSendNotification);
    }
    param=processor.getFloatParam(LFO_AMP_AMOUNT);
    if (&lfoAmpAmount && param->updateUiRequested()){
        lfoAmpAmount.setValue (param->uiGet(), dontSendNotification);
    }
    param=processor.getFloatParam(LFO_PITCH_AMOUNT);
    if (&lfoPitchAmount && param->updateUiRequested()){
        lfoPitchAmount.setValue (param->uiGet(), dontSendNotification);
    }
    param=processor.getFloatParam(LFO_INIT_PHASE);
    if (&lfoInitPhase && param->updateUiRequested()){
        lfoInitPhase.setValue (param->uiGet(), dontSendNotification);
    }
    IntParam *intParam=processor.getIntParam(ALGORITHM);
    if (&algorithm && intParam->updateUiRequested()){
        algorithm.setSelectedId (intParam->uiGet(), dontSendNotification);
    }
    intParam = processor.getIntParam(SCALE_ROOT);
    if (&scaleRoot && intParam->updateUiRequested()){
        scaleRoot.setSelectedId(intParam->uiGet(), dontSendNotification);
    }
    intParam = processor.getIntParam(LFO_SHAPE);
    if (&lfoShape && intParam->updateUiRequested()){
        lfoShape.setSelectedId(intParam->uiGet() + 1, dontSendNotification);
    }
    StringParam *stringParam = processor.getStringParam(SCALE);
    if (&tuningEditor && stringParam->updateUiRequested())
        tuningEditor.setText(stringParam->uiGet());
        
}