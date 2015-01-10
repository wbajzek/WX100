/*
  ==============================================================================

    Wx100RatioSlider.h
    Created: 10 Jan 2015 1:56:12pm
    Author:  William Bajzek

  ==============================================================================
*/

#ifndef WX100RATIOSLIDER_H_INCLUDED
#define WX100RATIOSLIDER_H_INCLUDED

#include "JuceHeader.h"
#include "Wx100.h"

class Wx100RatioSlider : public Slider
{
public:
    Wx100RatioSlider(String name)
    {
    }
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
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Wx100RatioSlider)
};


#endif  // WX100RATIOSLIDER_H_INCLUDED
