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

#ifndef __JUCE_HEADER_DA44287BDE525596__
#define __JUCE_HEADER_DA44287BDE525596__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "Wx100.h"
#include "Wx100AudioProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Wx100AdvancedEditor  : public AudioProcessorEditor,
                             public TextEditorListener,
                             public ComboBoxListener,
                             public Timer
{
public:
    //==============================================================================
    Wx100AdvancedEditor (Wx100AudioProcessor& newProcessor);
    ~Wx100AdvancedEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void textEditorTextChanged (TextEditor& editor);
    void textEditorReturnKeyPressed (TextEditor&);
    void textEditorEscapeKeyPressed (TextEditor&);
    void textEditorFocusLost (TextEditor&);
    void timerCallback();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Wx100AudioProcessor& processor;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextEditor> scaleEditor;
    ScopedPointer<Label> scaleLabel;
    ScopedPointer<ComboBox> scaleRoot;
    ScopedPointer<ComboBox> voiceCount;
    ScopedPointer<Label> voiceCountLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Wx100AdvancedEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_DA44287BDE525596__
