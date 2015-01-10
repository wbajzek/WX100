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

#include "Wx100AlgorithmSelector.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Wx100AlgorithmSelector::Wx100AlgorithmSelector ()
{

    //[UserPreSize]
    //[/UserPreSize]

    setSize (112, 468);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Wx100AlgorithmSelector::~Wx100AlgorithmSelector()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Wx100AlgorithmSelector::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff2b2b2b));

    g.setColour (Colour (0x7f00a809));
    g.fillRect (40, 40, 40, 40);

    g.setColour (Colour (0xff00ff19));
    g.drawRect (40, 40, 40, 40, 5);

    g.setColour (Colour (0x7f00a809));
    g.fillRect (40, 160, 40, 40);

    g.setColour (Colour (0xff00ff19));
    g.drawRect (40, 160, 40, 40, 5);

    g.setColour (Colour (0x7f00a809));
    g.fillRect (40, 280, 40, 40);

    g.setColour (Colour (0xff00ff19));
    g.drawRect (40, 280, 40, 40, 5);

    g.setColour (Colour (0x7f00a809));
    g.fillRect (40, 400, 40, 40);

    g.setColour (Colour (0xff00ff19));
    g.drawRect (40, 400, 40, 40, 5);

    g.setColour (Colours::azure);
    g.setFont (Font (28.60f, Font::plain));
    g.drawText (TRANS("D"),
                40, 40, 40, 40,
                Justification::centred, true);

    g.setColour (Colours::azure);
    g.setFont (Font (28.60f, Font::plain));
    g.drawText (TRANS("C"),
                40, 160, 40, 40,
                Justification::centred, true);

    g.setColour (Colours::azure);
    g.setFont (Font (28.60f, Font::plain));
    g.drawText (TRANS("B"),
                40, 280, 40, 40,
                Justification::centred, true);

    g.setColour (Colours::azure);
    g.setFont (Font (28.60f, Font::plain));
    g.drawText (TRANS("A"),
                40, 400, 40, 40,
                Justification::centred, true);

    //[UserPaint] Add your own custom painting code here..
    g.setColour(Colour (0x7f00a809));
    // operator 4 feedback
    g.drawLine(Line<float>(60,40,60,22), 4);
    g.drawLine(Line<float>(58,20,102,20), 4);
    g.drawLine(Line<float>(100,22,100,62), 4);
    g.drawArrow(Line<float>(98, 60, 80, 60), 4, 10, 10);
    switch (algorithm) {
        case 0:
            g.drawArrow(Line<float>(60,80,60,160), 4, 10, 10);
            g.drawArrow(Line<float>(60,200,60,280), 4, 10, 10);
            g.drawArrow(Line<float>(60,320,60,400), 4, 10, 10);
            break;
        case 1:
            g.drawLine(Line<float>(40,60,20,60),4);
            g.drawLine(Line<float>(22,62,22,302),4);
            g.drawArrow(Line<float>(22,300,40,300), 4, 10, 10);
            g.drawArrow(Line<float>(60,200,60,280), 4, 10, 10);
            g.drawArrow(Line<float>(60,320,60,400), 4, 10, 10);
            break;
        case 2:
            g.drawLine(Line<float>(40,60,20,60),4);
            g.drawLine(Line<float>(22,62,22,422),4);
            g.drawArrow(Line<float>(24,420,40,420), 4, 10, 10);
            g.drawArrow(Line<float>(60,200,60,280), 4, 10, 10);
            g.drawArrow(Line<float>(60,320,60,400), 4, 10, 10);
            break;
        case 3:
            g.drawArrow(Line<float>(60,80,60,160), 4, 10, 10);
            g.drawArrow(Line<float>(60,320,60,400), 4, 10, 10);
            g.drawLine(Line<float>(40,180,20,180),4);
            g.drawLine(Line<float>(22,182,22,422),4);
            g.drawArrow(Line<float>(24,420,40,420), 4, 10, 10);
            break;
        case 4:
            g.drawArrow(Line<float>(60,80,60,160), 4, 10, 10);
            g.drawArrow(Line<float>(60,320,60,400), 4, 10, 10);
            break;
        case 5:
            g.drawLine(Line<float>(40,60,20,60),4);
            g.drawLine(Line<float>(22,62,22,422),4);
            g.drawArrow(Line<float>(24,180,40,180), 4, 10, 10);
            g.drawArrow(Line<float>(24,300,40,300), 4, 10, 10);
            g.drawArrow(Line<float>(24,420,40,420), 4, 10, 10);
            break;
        case 6:
            g.drawArrow(Line<float>(60,80,60,160), 4, 10, 10);
            break;
        case 7:
            break;
        default:
            break;
    }
    //[/UserPaint]
}

void Wx100AlgorithmSelector::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Wx100AlgorithmSelector" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="112" initialHeight="468">
  <BACKGROUND backgroundColour="ff2b2b2b">
    <RECT pos="40 40 40 40" fill="solid: 7f00a809" hasStroke="1" stroke="5, mitered, butt"
          strokeColour="solid: ff00ff19"/>
    <RECT pos="40 160 40 40" fill="solid: 7f00a809" hasStroke="1" stroke="5, mitered, butt"
          strokeColour="solid: ff00ff19"/>
    <RECT pos="40 280 40 40" fill="solid: 7f00a809" hasStroke="1" stroke="5, mitered, butt"
          strokeColour="solid: ff00ff19"/>
    <RECT pos="40 400 40 40" fill="solid: 7f00a809" hasStroke="1" stroke="5, mitered, butt"
          strokeColour="solid: ff00ff19"/>
    <TEXT pos="40 40 40 40" fill="solid: fff0ffff" hasStroke="0" text="D"
          fontname="Default font" fontsize="28.600000000000001421" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="40 160 40 40" fill="solid: fff0ffff" hasStroke="0" text="C"
          fontname="Default font" fontsize="28.600000000000001421" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="40 280 40 40" fill="solid: fff0ffff" hasStroke="0" text="B"
          fontname="Default font" fontsize="28.600000000000001421" bold="0"
          italic="0" justification="36"/>
    <TEXT pos="40 400 40 40" fill="solid: fff0ffff" hasStroke="0" text="A"
          fontname="Default font" fontsize="28.600000000000001421" bold="0"
          italic="0" justification="36"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
