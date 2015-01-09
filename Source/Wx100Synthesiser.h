/*
  ==============================================================================

    Wx100Synthesiser.h
    Created: 26 Dec 2014 10:58:54pm
    Author:  William Bajzek

  ==============================================================================
*/

#ifndef WX100SYNTHESISER_H_INCLUDED
#define WX100SYNTHESISER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Synth.h"
#include "Wx100.h"

class Wx100SynthSound : public SynthesiserSound
{
public:
    Wx100SynthSound();
    
    bool appliesToNote(const int /*midiNoteNumber*/);
    bool appliesToChannel(const int /*midiChannel*/);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Wx100SynthSound);
};


class Wx100Synthesiser : public Synthesiser
{
public:
    void refreshCurrentPlaybackSampleRate ();

protected:
    /** Chooses a voice that is most suitable for being re-used.
     The default method will attempt to find the oldest voice that isn't the
     bottom or top note being played. If that's not suitable for your synth,
     you can override this method and do something more cunning instead.
     */
    SynthesiserVoice* findVoiceToSteal (SynthesiserSound* soundToPlay,
                                        int midiChannel,
                                        int midiNoteNumber) const;
};


class Wx100SynthVoice : public SynthesiserVoice, public ActionListener
{
public:
    Wx100SynthVoice(float* parameters, int* algorithm, int* lfoShape, int* scaleRoot, Frequency* tuningTable);
    ~Wx100SynthVoice();
    bool canPlaySound (SynthesiserSound* sound);
    void startNote (const int midiNoteNumber, const float velocity, SynthesiserSound* /*sound*/, const int currentPitchWheelPosition);
    void stopNote (float velocity, const bool allowTailOff);
    void pitchWheelMoved (const int newValue);
    void controllerMoved (const int /*controllerNumber*/, const int /*newValue*/);
    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples);
    Amplitude getSample(Frequency freq);
    void aftertouchChanged (int newAftertouchValue);
    void setCurrentPlaybackSampleRate (double newRate);
    bool isPlayingChannel (int midiChannel) const;
    bool isVoiceActive() const;
    void actionListenerCallback (const String &message);
    Frequency* getTuningTable();
    
private:
    
    SynthVoice operators[numOperators];
    Oscillator lfo;
    float *localParameters;
    int *localAlgorithm;
    int *localScaleRoot;
    int *localLfoShape;
    int note = 0;
    int noteNumber;
    Frequency freq;
    Frequency *localTuningTable;
    bool voiceIsActive = false;
    Frequency sampleRate = 0.0;
    float modWheel = 0.00;
    
    Frequency calculateFrequency(int currentPitchWheelPosition);

    int getScaleRoot() {
        return *localScaleRoot - 1;
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Wx100SynthVoice);
};




#endif  // WX100SYNTHESISER_H_INCLUDED
