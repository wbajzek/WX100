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

#include "Wx100AdvancedEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Wx100AdvancedEditor::Wx100AdvancedEditor (Wx100AudioProcessor& newProcessor)
    : AudioProcessorEditor(newProcessor),
      processor(newProcessor)
{
    addAndMakeVisible (scaleEditor = new TextEditor ("scaleEditor"));
    scaleEditor->setMultiLine (true);
    scaleEditor->setReturnKeyStartsNewLine (true);
    scaleEditor->setReadOnly (false);
    scaleEditor->setScrollbarsShown (true);
    scaleEditor->setCaretVisible (true);
    scaleEditor->setPopupMenuEnabled (true);
    scaleEditor->setText (String::empty);

    addAndMakeVisible (scaleLabel = new Label ("scaleLabel",
                                               TRANS("Scala editor")));
    scaleLabel->setFont (Font (15.00f, Font::plain));
    scaleLabel->setJustificationType (Justification::centredLeft);
    scaleLabel->setEditable (false, false, false);
    scaleLabel->setColour (TextEditor::textColourId, Colours::black);
    scaleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (scaleRoot = new ComboBox ("scaleRoot"));
    scaleRoot->setEditableText (false);
    scaleRoot->setJustificationType (Justification::centredLeft);
    scaleRoot->setTextWhenNothingSelected (String::empty);
    scaleRoot->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    scaleRoot->addListener (this);

    addAndMakeVisible (voiceCount = new ComboBox ("voiceCount"));
    voiceCount->setEditableText (false);
    voiceCount->setJustificationType (Justification::centredLeft);
    voiceCount->setTextWhenNothingSelected (String::empty);
    voiceCount->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    voiceCount->addListener (this);

    addAndMakeVisible (voiceCountLabel = new Label ("voiceCountLabel",
                                                    TRANS("Voices")));
    voiceCountLabel->setFont (Font (15.00f, Font::plain));
    voiceCountLabel->setJustificationType (Justification::centredLeft);
    voiceCountLabel->setEditable (false, false, false);
    voiceCountLabel->setColour (TextEditor::textColourId, Colours::black);
    voiceCountLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (690, 510);


    //[Constructor] You can add your own custom stuff here..
    StringArray scaleRootLabels;
    for (int i = 0; i < 9; i++)
    {
        scaleRootLabels.add(String("C") += i);
        scaleRootLabels.add(String("C#") += i);
        scaleRootLabels.add(String("D") += i);
        scaleRootLabels.add(String("D#") += i);
        scaleRootLabels.add(String("E") += i);
        scaleRootLabels.add(String("F") += i);
        scaleRootLabels.add(String("F#") += i);
        scaleRootLabels.add(String("G") += i);
        scaleRootLabels.add(String("G#") += i);
        scaleRootLabels.add(String("A") += i);
        scaleRootLabels.add(String("A#") += i);
        scaleRootLabels.add(String("B") += i);
    }
    scaleRoot->setItemEnabled(0, false);
    scaleRoot->setEditableText(false);
    scaleRoot->addItemList(scaleRootLabels, 1);
    scaleRoot->setWantsKeyboardFocus(false);

    voiceCount->setItemEnabled(0, false);
    voiceCount->addItem("1",1);
    voiceCount->addItem("2",2);
    voiceCount->addItem("4",4);
    voiceCount->addItem("8",8);
    voiceCount->addItem("16",16);
    voiceCount->addItem("24",24);
    voiceCount->addItem("32",32);
    voiceCount->setEditableText(false);

    scaleEditor->addListener(this);
    processor.updateUi(true,true);
    timerCallback();
    startTimer(50);
    //[/Constructor]
}

Wx100AdvancedEditor::~Wx100AdvancedEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    scaleEditor = nullptr;
    scaleLabel = nullptr;
    scaleRoot = nullptr;
    voiceCount = nullptr;
    voiceCountLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Wx100AdvancedEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Wx100AdvancedEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    scaleEditor->setBounds (16, 32, 376, 432);
    scaleLabel->setBounds (16, 8, 150, 24);
    scaleRoot->setBounds (16, 472, 150, 24);
    voiceCount->setBounds (400, 32, 72, 24);
    voiceCountLabel->setBounds (400, 8, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Wx100AdvancedEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == scaleRoot)
    {
        //[UserComboBoxCode_scaleRoot] -- add your combo box handling code here..
        processor.getIntParam(SCALE_ROOT)->updateProcessorAndHostFromUi(comboBoxThatHasChanged->getSelectedId() - 1);
        //[/UserComboBoxCode_scaleRoot]
    }
    else if (comboBoxThatHasChanged == voiceCount)
    {
        //[UserComboBoxCode_voiceCount] -- add your combo box handling code here..
        processor.getIntParam(VOICE_COUNT)->updateProcessorAndHostFromUi(comboBoxThatHasChanged->getSelectedId());
        //[/UserComboBoxCode_voiceCount]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
/** Called when the user changes the text in some way. */
void Wx100AdvancedEditor::textEditorTextChanged (TextEditor& editor)
{
    processor.getStringParam(SCALE)->updateProcessorAndHostFromUi(editor.getText());
}

/** Called when the user presses the return key. */
void Wx100AdvancedEditor::textEditorReturnKeyPressed (TextEditor& editor)
{
    processor.getStringParam(SCALE)->updateProcessorAndHostFromUi(editor.getText());
}

/** Called when the user presses the escape key. */
void Wx100AdvancedEditor::textEditorEscapeKeyPressed (TextEditor& editor)
{
    processor.getStringParam(SCALE)->updateProcessorAndHostFromUi(editor.getText());
}

/** Called when the text editor loses focus. */
void Wx100AdvancedEditor::textEditorFocusLost (TextEditor& editor)
{
    processor.getStringParam(SCALE)->updateProcessorAndHostFromUi(editor.getText());
}

void Wx100AdvancedEditor::timerCallback()
{
    StringParam *param = processor.getStringParam(SCALE);
    if (&scaleEditor && param->updateUiRequested()){
        scaleEditor->setText (param->uiGet(), dontSendNotification);
    }
    IntParam *intParam = processor.getIntParam(SCALE_ROOT);
    if (&scaleRoot && intParam->updateUiRequested()){
        scaleRoot->setSelectedId(intParam->uiGet() + 1, dontSendNotification);
    }
    intParam = processor.getIntParam(VOICE_COUNT);
    if (&voiceCount && intParam->updateUiRequested()){
        voiceCount->setSelectedId(intParam->uiGet(), dontSendNotification);
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Wx100AdvancedEditor" componentName=""
                 parentClasses="public AudioProcessorEditor, public TextEditorListener, public ComboBoxListener, public Timer"
                 constructorParams="Wx100AudioProcessor&amp; newProcessor" variableInitialisers="AudioProcessorEditor(newProcessor),&#10;processor(newProcessor)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="690" initialHeight="510">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTEDITOR name="scaleEditor" id="a2cf9598d5ec2ef3" memberName="scaleEditor"
              virtualName="" explicitFocusOrder="0" pos="16 32 376 432" initialText=""
              multiline="1" retKeyStartsLine="1" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="scaleLabel" id="c56fba7a12a5d00f" memberName="scaleLabel"
         virtualName="" explicitFocusOrder="0" pos="16 8 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Scala editor" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="scaleRoot" id="6caec9eace4f02f8" memberName="scaleRoot"
            virtualName="" explicitFocusOrder="0" pos="16 472 150 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="voiceCount" id="7029ad1eb9ac7e7e" memberName="voiceCount"
            virtualName="" explicitFocusOrder="0" pos="400 32 72 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="voiceCountLabel" id="ee14fa6c0211c07a" memberName="voiceCountLabel"
         virtualName="" explicitFocusOrder="0" pos="400 8 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Voices" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
