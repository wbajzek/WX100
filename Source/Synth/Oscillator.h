/*
  ==============================================================================

    Oscillator.h
    Created: 11 Dec 2014 8:49:09am
    Author:  William Bajzek

  ==============================================================================
*/

#ifndef OSCILLATOR_H_INCLUDED
#define OSCILLATOR_H_INCLUDED

class Oscillator
{
public:
    
    Oscillator()
    {
    }

    ~Oscillator()
    {
    }
    
    void setPhase(float phase)
    {
        index = (int)(waveTableLength * phase) << 16;
    }
    
    void setFrequency(Frequency newFrequency)
    {
        if (frequency != newFrequency)
        {
            frequency = newFrequency;
            increment = (long)(frqTI * frequency) << 16;
        }
    }
    
    Frequency getFrequency() {
        return frequency;
    }
    
    void setSampleRate(float newSampleRate)
    {
        sampleRate = newSampleRate;
        frqTI = waveTableLength/sampleRate;
        increment = (long)(frqTI * frequency) << 16;
    }
    
    void setWaveTable(int newWaveTableShape)
    {
        waveTableShape = newWaveTableShape;
    }

    void setFm(Amplitude amount)
    {
        fm = amount;
    }
    
    Amplitude tick()
    {
        int scaledIndex = (((index+0x8000) >> 16) + (int)(waveTableLength * fm)) & (waveTableLength - 1);

        switch (waveTableShape)
        {
            case SINE_WAVE_TABLE:
                value = sineWaveTable[scaledIndex];
                break;
            case TRIANGLE_WAVE_TABLE:
                value = triangleWaveTable[scaledIndex];
                break;
            case SAW_WAVE_TABLE:
                value = sawWaveTable[scaledIndex];
                break;
            case RAMP_WAVE_TABLE:
                value = rampWaveTable[scaledIndex];
                break;
            case WHITE_NOISE_WAVE_TABLE:
                value = whiteNoiseWaveTable[scaledIndex];
                break;
            default:
                break;
        }

        index = index + increment & ((waveTableLength << 16) - 1);
        return value;
    }
    
    Amplitude output()
    {
        return value;
    }
    
private:
    Frequency sampleRate = 0.0;
    double frqTI = 0.0;
    Frequency frequency = 0.0;
    long increment = 0.0;
    unsigned long index = 0;
    int waveTableShape = 0;
    Amplitude value = 0.0;
    Amplitude fm = 0.0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};


#endif  // OSCILLATOR_H_INCLUDED
