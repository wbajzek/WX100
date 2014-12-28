/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "Wx100AudioProcessor.h"
#include "Wx100Editor.h"


//==============================================================================
Wx100AudioProcessorEditor::Wx100AudioProcessorEditor (Wx100AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (450, 350);
    for (int i = 0; i < numOperators; ++i)
    {
        amp[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        amp[i].setSize(50, 50);
        amp[i].setRange(0.0, 1.0, 0.001);
        amp[i].setScrollWheelEnabled(false);
        amp[i].setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
        amp[i].addListener(this);
        addAndMakeVisible(amp[i]);

        coarse[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        coarse[i].setSize(50, 50);
        coarse[i].setRange(1.0, 10.0, 1.0);
        coarse[i].setScrollWheelEnabled(false);
        coarse[i].setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
        coarse[i].addListener(this);
        addAndMakeVisible(coarse[i]);

        tuning[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        tuning[i].setSize(50, 50);
        tuning[i].setRange(-1.0, 1.0, 0.001);
        tuning[i].setScrollWheelEnabled(false);
        tuning[i].setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
        tuning[i].addListener(this);
        addAndMakeVisible(tuning[i]);

        attack[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        attack[i].setSize(50, 50);
        attack[i].setRange(0.0, 1.0, 0.001);
        attack[i].setScrollWheelEnabled(false);
        attack[i].setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
        attack[i].addListener(this);
        addAndMakeVisible(attack[i]);

        decay[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        decay[i].setSize(50, 50);
        decay[i].setRange(0.0, 10.0, 0.001);
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
        release[i].setRange(0.0, 1.0, 0.001);
        release[i].setScrollWheelEnabled(false);
        release[i].setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
        release[i].addListener(this);
        addAndMakeVisible(release[i]);
    }
    
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
    g.drawFittedText ("Amp", 20, 0, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Crse", 80, 0, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Tune", 140, 0, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Atk", 200, 0, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Dcy", 260, 0, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Sus", 320, 0, 50, 25, Justification::centred, 1);
    g.drawFittedText ("Rel", 380, 0, 50, 25, Justification::centred, 1);
}

void Wx100AudioProcessorEditor::resized()
{
    for (int i = 0; i < numOperators; ++i) {
        amp[i].setBounds (20, 20 + (60 * i), 20, 20);
        coarse[i].setBounds (80, 20 + (60 * i), 20, 20);
        tuning[i].setBounds (140, 20 + (60 * i), 20, 20);
        attack[i].setBounds (200, 20 + (60 * i), 20, 20);
        decay[i].setBounds (260, 20 + (60 * i), 20, 20);
        sustain[i].setBounds (320, 20 + (60 * i), 20, 20);
        release[i].setBounds (380, 20 + (60 * i), 20, 20);
    }
}

void Wx100AudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    for (int i = 0; i < numOperators; ++i) {
        if (slider == &amp[i])
            processor.getFloatParam(AMP_1 + i)->updateProcessorAndHostFromUi(slider->getValue());
        if (slider == &coarse[i])
            processor.getFloatParam(COARSE_1 + i)->updateProcessorAndHostFromUi(slider->getValue());
        if (slider == &tuning[i])
            processor.getFloatParam(TUNING_1 + i)->updateProcessorAndHostFromUi(slider->getValue());
        if (slider == &attack[i])
            processor.getFloatParam(ATTACK_1 + i)->updateProcessorAndHostFromUi(slider->getValue());
        if (slider == &decay[i])
            processor.getFloatParam(DECAY_1 + i)->updateProcessorAndHostFromUi(slider->getValue());
        if (slider == &sustain[i])
            processor.getFloatParam(SUSTAIN_1 + i)->updateProcessorAndHostFromUi(slider->getValue());
        if (slider == &release[i])
            processor.getFloatParam(RELEASE_1 + i)->updateProcessorAndHostFromUi(slider->getValue());
    }
}

void Wx100AudioProcessorEditor::timerCallback()
{
    for (int i = 0; i < numOperators; ++i)
    {
        FloatParam *param=processor.getFloatParam(AMP_1 + i);
        if (&amp[i] && param->updateUiRequested()){
            amp[i].setValue (param->uiGet(), dontSendNotification);
        }
        param=processor.getFloatParam(COARSE_1 + i);
        if (&coarse[i] && param->updateUiRequested()){
            coarse[i].setValue (param->uiGet(), dontSendNotification);
        }
        param=processor.getFloatParam(TUNING_1 + i);
        if (&tuning[i] && param->updateUiRequested()){
            tuning[i].setValue (param->uiGet(), dontSendNotification);
        }
        param=processor.getFloatParam(ATTACK_1 + i);
        if (&attack[i] && param->updateUiRequested()){
            attack[i].setValue (param->uiGet(), dontSendNotification);
        }
        param=processor.getFloatParam(DECAY_1 + i);
        if (&decay[i] && param->updateUiRequested()){
            decay[i].setValue (param->uiGet(), dontSendNotification);
        }
        param=processor.getFloatParam(SUSTAIN_1 + i);
        if (&sustain[i] && param->updateUiRequested()){
            sustain[i].setValue (param->uiGet(), dontSendNotification);
        }
        param=processor.getFloatParam(RELEASE_1 + i);
        if (&release[i] && param->updateUiRequested()){
            release[i].setValue (param->uiGet(), dontSendNotification);
        }
    }
}