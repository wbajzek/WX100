/*
  ==============================================================================

    SclParser.h
    Created: 1 Jan 2015 9:17:57am
    Author:  William Bajzek

  ==============================================================================
*/

#ifndef SCLPARSER_H_INCLUDED
#define SCLPARSER_H_INCLUDED

#include "../../JuceLibraryCode/JuceHeader.h"

const Frequency frequencyRef = 440.0;
const int noteRef = 69;

class SclParser
{
public:
    static void parse(String sclFile, double *frequencies, int scaleRoot)
    {
        StringArray lines;
        lines.addLines(StringRef(sclFile));
        for (int i = 0; i < lines.size(); ++i)
        {
            if (lines[i].startsWith("!") || lines[i].isEmpty())
            {
                lines.remove(i);
                --i;
            }
        }
        
        // If SCL is invalid, default to standard 12EDO

        if (lines.size() < 3)
        {
            for (int i = 1; i < 128; ++i)
                frequencies[i] = 8.1758 * pow(2.0, i * 100.0 / 1200.0); // in cents above root
            return;
        }

        int degrees = lines[1].getIntValue();
        int lowestDegree = scaleRoot - (degrees * (scaleRoot / degrees));
        
        lines.removeRange(0, 2);
        lines.insert(0, "1/1");
        Frequency root = frequencyRef * pow(2.0, (((lowestDegree + 3) / 12)) - 6 + ((lowestDegree + 3) % 12)/12.0);
        
        for (int i = lowestDegree, line = 0; i < 128; ++i)
        {
            String interval = String(lines[line]).trim();
            if (intervalIsInCents(interval))
                frequencies[i] = root * pow(2.0, interval.getDoubleValue() / 1200.0); // in cents above root
            else // interval is fraction
            {
                frequencies[i] = root * intervalFromFraction(interval);
            }
            line++;
            if (line == lines.size())
            {
                line = 1;
                root = frequencies[i];
            }
        }

    }
private:
    
    static bool intervalIsInCents(String interval)
    {
        return interval.containsChar('.');
    }
    
    static double intervalFromFraction(String interval)
    {
        int indexOfSlash = interval.indexOfChar('/');
        int numerator, denominator;
        if (indexOfSlash >= 0)
        {
            numerator = interval.substring(0, indexOfSlash).getIntValue();
            denominator = interval.substring(indexOfSlash + 1).getIntValue();
        }
        else {
            numerator = interval.getIntValue();
            denominator = 1;
        }
        
        return (double)numerator / (double)denominator;
    }

};

#endif  // SCLPARSER_H_INCLUDED