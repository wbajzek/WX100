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

bool intervalIsInCents(String interval)
{
    return interval.containsChar('.');
}

double intervalFromFraction(String interval)
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

void parseScl(String sclFile, double *frequencies)
{
    StringArray lines;
    lines.addLines(StringRef(sclFile));
    for (int i = 0; i < lines.size(); ++i)
    {
        if (lines[i].startsWith("!"))
        {
            lines.remove(i);
            --i;
        }
    }
    
    double root = frequencies[0];
    Logger::writeToLog("\n\n\n");
    Logger::writeToLog(String(root));
    for (int i = 1, line = 2; i < 128; ++i)
    {
        String interval = String(lines[line]).trim();
        if (intervalIsInCents(interval))
            frequencies[i] = root * pow(2.0, interval.getDoubleValue() / 1200.0); // in cents above root
        else // interval is fraction
        {
            frequencies[i] = root * intervalFromFraction(interval);
        }
        Logger::writeToLog(String(frequencies[i]));
        line++;
        if (line == lines.size())
        {
            line = 2;
            root = frequencies[i];
        }
    }
}

#endif  // SCLPARSER_H_INCLUDED
