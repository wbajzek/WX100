/*
  ==============================================================================

    SynthVoice.h
    Created: 20 Dec 2014 10:06:47am
    Author:  William Bajzek

  ==============================================================================
*/

#ifndef SYNTHVOICE_H_INCLUDED
#define SYNTHVOICE_H_INCLUDED

class SynthVoice
{
public:
    SynthVoice() {
        
    }
    ~SynthVoice() {
    }

    
    void setSampleRate(Frequency newRate)
    {
        sampleRate = newRate;
        oscillator.setSampleRate(newRate);
        envelope.setSampleRate(newRate);
    }
    
    void setWaveTable(int newWaveTableShape)
    {
        oscillator.setWaveTable(newWaveTableShape);
    }
    
    void setAdsr(Adsr newAdsr)
    {
        envelope.setAdsr(newAdsr);
    }

    void trigger(Amplitude newVelocity) {
        velocity = newVelocity;
        envelope.trigger();
    }
    
    void triggerRelease() {
        envelope.triggerRelease();
    }

    void stop() {
        envelope.triggerDead();
    }
    
    void setPhase(float phase)
    {
        oscillator.setPhase(phase);
    }
    
    void setFrequency(Frequency newFrequency)
    {
        oscillator.setFrequency(newFrequency);
    }
    
    Frequency getFrequency()
    {
        return oscillator.getFrequency();
    }
    
    void setFm(Amplitude amount)
    {
        oscillator.setFm(amount);
    }
    
    void tick()
    {
        currentAmplitude = envelope.tick();
        if (currentAmplitude > 0.0)
            if ((currentAmplitude *= velocity) > 0.0)
                currentSample = oscillator.tick() * currentAmplitude;
    }
        
    bool isActive() const
    {
        return envelope.isActive();
    }

    Amplitude currentSample = 0.0;
    Amplitude currentAmplitude = 0.0;
    Oscillator oscillator;
    Envelope envelope;

private:
    Frequency sampleRate;
    Amplitude velocity;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthVoice)
};



#endif  // SYNTHVOICE_H_INCLUDED
