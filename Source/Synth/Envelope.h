/*
  ==============================================================================

    Envelope.h
    Created: 11 Dec 2014 12:17:37pm
    Author:  William Bajzek

  ==============================================================================
*/

#ifndef ENVELOPE_H_INCLUDED
#define ENVELOPE_H_INCLUDED

struct Adsr
{
    Seconds attack = 0.0;
    Seconds decay = 0.0;
    Amplitude sustainLevel = 1.0;
    Seconds release = 0.0;
};

class Envelope
{
public:

    Envelope()
    {        
    }
    
    ~Envelope()
    {
    }
    
    void setSampleRate(float newRate)
    {
        sampleRate = newRate;
        convertSecondsToSamples();
    }
    
    // parameters in seconds
    void setAdsr(Adsr newAdsr)
    {
        adsr = newAdsr;
        convertSecondsToSamples();
    }
    
    // velocity scaled [0,1]
    void trigger()
    {
        envelopeState = ATTACK_STATE;
        if (attackSamples == 0)
        {
            envLevel = 1.0;
            envIncrement = 0.0;
            triggerDecay();
        }
        else
        {
            envIncrement = 1.0 / attackSamples;
            envCoefficient = 0.0;
        }
    }
    
    void triggerDecay()
    {
        envelopeState = DECAY_STATE;
        envIncrement = 0.0;
        envCoefficient = getSegmentCoefficient(envLevel, adsr.sustainLevel, decaySamples);
    }
    
    void triggerSustain()
    {
        envLevel = adsr.sustainLevel;
        envIncrement = 0.0;
        envCoefficient = 0.0;
    }
    
    void triggerRelease()
    {
        envelopeState = RELEASE_STATE;
        envIncrement = 0.0;
        envCoefficient = getSegmentCoefficient(envLevel, 0.0, releaseSamples);
    }
    
    void triggerDead()
    {
        envelopeState = DEAD_STATE;
        envLevel = 0.0;
    }

    Amplitude tick() {
        if (envelopeState != DEAD_STATE) {
            envLevel += envIncrement + (envCoefficient * envLevel);
            if (envLevel >= 1.0)
                triggerDecay();
            else if (envelopeState == DECAY_STATE && envLevel <= adsr.sustainLevel)
                triggerSustain();
            else if (envelopeState != ATTACK_STATE && envLevel <= 0.001)
                triggerDead();
        }
        return envLevel;
    }
    
    Amplitude amplitude()
    {
        return envLevel;
    }
    
    bool isActive() const
    {
        return envelopeState != DEAD_STATE;
    }

    int envelopeState = DEAD_STATE;
    
    enum EnvelopeState {
        ATTACK_STATE,
        DECAY_STATE,
        SUSTAIN_STATE,
        RELEASE_STATE,
        DEAD_STATE,
    };
    
private:
    
    inline Amplitude getSegmentCoefficient(Amplitude startLevel, Amplitude endLevel, int durationInSamples) const
    {
        // add a tiny fudge factor when calculating because it doesn't work when levels are exactly 0.0
        return (log((endLevel + 0.0001)) - log(startLevel + 0.0001)) / durationInSamples;
    }
    
    void convertSecondsToSamples()
    {
        attackSamples = sampleRate * adsr.attack;
        decaySamples = sampleRate * adsr.decay;
        releaseSamples = sampleRate * adsr.release;
    }
    
    Frequency sampleRate = 0.0;
    Amplitude envLevel = 0.0;
    float envCoefficient = 0.0;
    float envIncrement = 0.0;

    Adsr adsr;

    unsigned long attackSamples = 0;
    unsigned long decaySamples = 0;
    unsigned long releaseSamples = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};



#endif  // ENVELOPE_H_INCLUDED
