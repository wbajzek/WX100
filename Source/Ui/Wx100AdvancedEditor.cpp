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
Wx100AdvancedEditor::Wx100AdvancedEditor ()
{
    addAndMakeVisible (textEditor = new TextEditor ("new text editor"));
    textEditor->setMultiLine (false);
    textEditor->setReturnKeyStartsNewLine (false);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (true);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (true);
    textEditor->setText (String::empty);

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
    voiceCount->addItem (TRANS("1"), 1);
    voiceCount->addItem (TRANS("2"), 2);
    voiceCount->addItem (TRANS("4"), 3);
    voiceCount->addItem (TRANS("8"), 4);
    voiceCount->addItem (TRANS("16"), 5);
    voiceCount->addItem (TRANS("24"), 6);
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
    //[/Constructor]
}

Wx100AdvancedEditor::~Wx100AdvancedEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    textEditor = nullptr;
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

    textEditor->setBounds (16, 32, 152, 432);
    scaleLabel->setBounds (16, 8, 150, 24);
    scaleRoot->setBounds (16, 472, 150, 24);
    voiceCount->setBounds (192, 32, 72, 24);
    voiceCountLabel->setBounds (192, 8, 150, 24);
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
        //[/UserComboBoxCode_scaleRoot]
    }
    else if (comboBoxThatHasChanged == voiceCount)
    {
        //[UserComboBoxCode_voiceCount] -- add your combo box handling code here..
        //[/UserComboBoxCode_voiceCount]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Wx100AdvancedEditor" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="690" initialHeight="510">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTEDITOR name="new text editor" id="a2cf9598d5ec2ef3" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="16 32 152 432" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
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
            virtualName="" explicitFocusOrder="0" pos="192 32 72 24" editable="0"
            layout="33" items="1&#10;2&#10;4&#10;8&#10;16&#10;24" textWhenNonSelected=""
            textWhenNoItems="(no choices)"/>
  <LABEL name="voiceCountLabel" id="ee14fa6c0211c07a" memberName="voiceCountLabel"
         virtualName="" explicitFocusOrder="0" pos="192 8 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Voices" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
