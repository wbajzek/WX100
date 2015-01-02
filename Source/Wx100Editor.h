/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Wx100AudioProcessor.h"
#include "Wx100TuningEditor.h"
#include "Wx100.h"

//==============================================================================
/**
*/

class Wx100RatioSlider : public Slider
{
public:
    Wx100RatioSlider() {}
    ~Wx100RatioSlider() {}
    
    double snapValue(double attemptedValue, DragMode dragmode)
    {
        double snappedValue = ratios[0];
        int i = 0;
        while (attemptedValue > snappedValue)
            snappedValue = ratios[++i];
        return snappedValue;
    }
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Wx100RatioSlider)
};


class Wx100AudioProcessorEditor  : public AudioProcessorEditor,
private Slider::Listener, private ComboBox::Listener, private TextButton::Listener, private TextEditor::Listener, public Timer
{
public:
    Wx100AudioProcessorEditor (Wx100AudioProcessor&);
    ~Wx100AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider* slider) override;
    void comboBoxChanged (ComboBox* comboBox) override;
    void buttonClicked(Button* button) override;
    void textEditorTextChanged (TextEditor& editor);
    void textEditorReturnKeyPressed (TextEditor&);
    void textEditorEscapeKeyPressed (TextEditor&);
    void textEditorFocusLost (TextEditor&);
    void timerCallback();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Wx100AudioProcessor& processor;

    Slider amp[numOperators];
    Wx100RatioSlider ratio[numOperators];
    Slider tuning[numOperators];
    Slider attack[numOperators];
    Slider decay[numOperators];
    Slider sustain[numOperators];
    Slider release[numOperators];
    Slider phase[numOperators];
    GroupComponent operators[numOperators];
    Slider feedback;
    Slider lfoFrequency;
    Slider lfoAmpAmount;
    Slider lfoPitchAmount;
    Slider lfoInitPhase;
    ComboBox lfoShape;
    ComboBox algorithm;
    TextButton scale;
    ComboBox scaleRoot;
    Wx100TuningEditor tuningEditor;
    Component::SafePointer<Component> editorWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Wx100AudioProcessorEditor)
};

#endif  // PLUGINEDITOR_H_INCLUDED
