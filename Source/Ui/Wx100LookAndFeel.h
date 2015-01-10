/*
 ==============================================================================
 
 Wx100LookAndFeel.h
 Created: 10 Jan 2015 2:15:42pm
 Author:  William Bajzek
 
 ==============================================================================
 */

#ifndef WX100LOOKANDFEEL_H_INCLUDED
#define WX100LOOKANDFEEL_H_INCLUDED

#include "JuceHeader.h"


struct Wx100LookAndFeel : public LookAndFeel_V3
{
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
    {
        const float diameter = jmin (width, height) * 0.7;
        const float radius = (diameter / 2.0f);
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float rw = radius * 2.0f;
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
        
        const Colour baseColour (slider.isEnabled() ? slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 0.9f : 1.0f)
                                 : Colour (0x80808080));
        
        Rectangle<float> r (rx, ry, rw, rw);

        AffineTransform t (AffineTransform::rotation (angle, r.getCentreX(), r.getCentreY()));
        
        float x1 = r.getTopLeft().getX(), y1 = r.getTopLeft().getY(), x2 = r.getBottomLeft().getX(), y2 = r.getBottomLeft().getY();
    
        g.setGradientFill (ColourGradient (baseColour, x1, y1,
                                           baseColour.darker (0.6f), x2, y2,
                                           false));
    
        Path knob;
        knob.addPolygon(Point<float>(centreX, centreY), 36, radius);
        g.fillPath (knob, t);
        g.setColour(baseColour.darker(1.0));
        Path ring;
        ring.addPolygon(Point<float>(centreX, centreY), 36, radius + 2.0);
        g.strokePath (ring, PathStrokeType(3));

        Path needle;
        Rectangle<float> r2 (r * 0.2f);
        Point<float> needlePoint = Point<float> (r.getCentreX() - (r2.getWidth() / 4.0), r.getY());
        needle.addPolygon(needlePoint, 36, radius * 0.15);

        g.setGradientFill (ColourGradient (Colours::white, x1, y1,
                                           Colours::white.darker (0.2f), x2, y2,
                                           false));
        g.fillPath (needle, AffineTransform::rotation (angle, r.getCentreX(), r.getCentreY()));
    }
};


#endif  // WX100LOOKANDFEEL_H_INCLUDED
