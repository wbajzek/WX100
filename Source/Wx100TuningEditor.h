/*
  ==============================================================================

    Wx100TuningEditor.h
    Created: 1 Jan 2015 4:43:23pm
    Author:  William Bajzek

  ==============================================================================
*/

#ifndef WX100TUNINGEDITOR_H_INCLUDED
#define WX100TUNINGEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Wx100AudioProcessor.h"
#include "Wx100.h"

class Wx100TuningEditor  : public Component
{
public:
    Wx100TuningEditor (TextEditorListener *listener);
    ~Wx100TuningEditor();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void setText(String text);
    
private:
    
    ScopedPointer<Wx100AudioProcessor> processor;
    TextEditor editor;
    TextButton submit;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Wx100TuningEditor)
};

#endif  // WX100TUNINGEDITOR_H_INCLUDED
