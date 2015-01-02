/*
  ==============================================================================

    Wx100TuningEditor.cpp
    Created: 1 Jan 2015 4:43:23pm
    Author:  William Bajzek

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Wx100TuningEditor.h"

//==============================================================================
Wx100TuningEditor::Wx100TuningEditor(TextEditorListener *listener) : Component()
{
    addAndMakeVisible(editor);
    editor.setMultiLine(true);
    editor.setTabKeyUsedAsCharacter(true);
    editor.setReturnKeyStartsNewLine(true);
    editor.setEscapeAndReturnKeysConsumed(true);
    editor.addListener(listener);
    setSize (590, 415);
    
    addAndMakeVisible(submit);
}

Wx100TuningEditor::~Wx100TuningEditor()
{
}

void Wx100TuningEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);   // clear the background
}

void Wx100TuningEditor::resized()
{
    editor.setBounds(getLocalBounds());
}

void Wx100TuningEditor::setText(String text)
{
    editor.setText(text, dontSendNotification);
}
