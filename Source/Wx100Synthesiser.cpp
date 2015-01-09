/*
  ==============================================================================

    Wx100Synthesiser.cpp
    Created: 26 Dec 2014 10:58:54pm
    Author:  William Bajzek

  ==============================================================================
*/

#include "Wx100Synthesiser.h"

Wx100SynthSound::Wx100SynthSound()
{
}

bool Wx100SynthSound::appliesToNote(const int /*midiNoteNumber*/)
{
    return true;
}
bool Wx100SynthSound::appliesToChannel(const int /*midiChannel*/)
{
    return true;
}


struct VoiceAgeSorter
{
    static int compareElements (SynthesiserVoice* v1, SynthesiserVoice* v2) noexcept
    {
        return v1->wasStartedBefore (*v2) ? 1 : (v2->wasStartedBefore (*v1) ? -1 : 0);
    }
};

SynthesiserVoice* Wx100Synthesiser::findVoiceToSteal (SynthesiserSound* soundToPlay,
                                                         int /*midiChannel*/, int midiNoteNumber) const
{
    // this is a list of voices we can steal, sorted by how long they've been running
    Array<SynthesiserVoice*> usableVoices;
    usableVoices.ensureStorageAllocated (voices.size());
    
    for (int i = 0; i < voices.size(); ++i)
    {
        SynthesiserVoice* const voice = voices.getUnchecked (i);
        VoiceAgeSorter sorter;
        usableVoices.addSorted (sorter, voice);
    }
    
    // steal the oldest note
    return usableVoices[voices.size()-1];
}


Wx100SynthVoice::Wx100SynthVoice(float *parameters, int *algorithm, int *lfoShape, int *scaleRoot, Frequency *tuningTable)
{
    localParameters = parameters;
    localAlgorithm = algorithm;
    localScaleRoot = scaleRoot;
    localTuningTable = tuningTable;
    localLfoShape = lfoShape;
    lfo.setFrequency(localParameters[LFO_FREQ]);
    lfo.setWaveTable(*localLfoShape);
    for (int i = 0; i < numOperators; ++i)
    {
        operators[i].setWaveTable(SINE_WAVE_TABLE);
    }
}

Wx100SynthVoice::~Wx100SynthVoice()
{
}

void Wx100SynthVoice::setCurrentPlaybackSampleRate(Frequency newSampleRate)
{
    sampleRate = newSampleRate;
    for (int i = 0; i < numOperators; ++i)
        operators[i].setSampleRate(newSampleRate);
    lfo.setSampleRate(sampleRate);
}


bool Wx100SynthVoice::canPlaySound (SynthesiserSound* sound)
{
    return true;
}

void Wx100SynthVoice::startNote (const int midiNoteNumber, const float midiVelocity, SynthesiserSound* /*sound*/, const int currentPitchWheelPosition)
{
    noteNumber = midiNoteNumber;
    freq = calculateFrequency(currentPitchWheelPosition);
    
    for (int i = 0; i < numOperators; ++i)
    {
        operators[i].setPhase(localParameters[PHASE_0 + i]);
        Adsr adsr;
        adsr.attack = localParameters[ATTACK_0 + i];
        adsr.decay = localParameters[DECAY_0 + i];
        adsr.sustainLevel = localParameters[SUSTAIN_0 + i];
        adsr.release = localParameters[RELEASE_0 + i];
        operators[i].setAdsr(adsr);
        operators[i].trigger(midiVelocity);
    }
    lfo.setPhase(localParameters[LFO_INIT_PHASE]);
    voiceIsActive = true;
}

void Wx100SynthVoice::stopNote (float velocity, const bool allowTailOff)
{
    for (int i = 0; i < numOperators; ++i)
        operators[i].triggerRelease();
}

Frequency Wx100SynthVoice::calculateFrequency(int currentPitchWheelPosition)
{
    float pbCents = ( (float)currentPitchWheelPosition / 16383.0) * (400.0) + -200.0;
    return localTuningTable[noteNumber] * pow(2, pbCents/1200);
}

void Wx100SynthVoice::pitchWheelMoved (const int currentPitchWheelPosition)
{
    freq = calculateFrequency(currentPitchWheelPosition);
}

void Wx100SynthVoice::controllerMoved (const int controllerNumber, const int newValue)
{
    switch (controllerNumber)
    {
        case MOD_WHEEL_CONTROL:
            modWheel = (float)newValue * 0.0078740157 * localParameters[LFO_PITCH_AMOUNT]; // 0.0078740157 = 1 / 127
            break;
        default:
            break;
    }
}

void Wx100SynthVoice::renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    const int numChannels = outputBuffer.getNumChannels();
    Amplitude sample;
    while (--numSamples >= 0 && getCurrentlyPlayingNote() != -1)
    {
        Amplitude lfoLevel = lfo.output();
        sample = getSample(freq + (freq * modWheel * lfoLevel)) * (0.25 + lfoLevel * localParameters[LFO_AMP_AMOUNT]);
        for (int i = 0; i < numChannels; ++i)
            outputBuffer.addSample(i, startSample, sample);

        for (int i = 0; i < numOperators; ++i)
            operators[i].tick();
        
        lfo.tick();
        ++startSample;
    }
}

Amplitude Wx100SynthVoice::getSample(Frequency freq)
{
    Amplitude sample = 0.0;
    for (int i = 0; i < numOperators; ++i)
    {
        Frequency ratioFreq = freq * localParameters[RATIO_0 + i];
        operators[i].setFrequency(ratioFreq + (ratioFreq * pow(2.0, localParameters[TUNING_0 + i] / 4.0))); // 4.0 for reasonable range
    }
    // last operator always feeds back
    operators[3].setFm(operators[3].currentSample * localParameters[FEEDBACK_3]);
    switch (*localAlgorithm)
    {
        case 1:
            if (operators[0].isActive())
            {
                operators[2].setFm(operators[3].currentSample * localParameters[AMP_3]);
                operators[1].setFm(operators[2].currentSample * localParameters[AMP_2]);
                operators[0].setFm(operators[1].currentSample * localParameters[AMP_1]);
                
                sample = operators[0].currentSample * localParameters[AMP_0];
            }
            else
                clearCurrentNote();
            break;
        case 2:
            if (operators[0].isActive())
            {
                operators[2].setFm(0.0);
                operators[1].setFm(operators[2].currentSample * localParameters[AMP_2] +
                                   (operators[3].currentSample * localParameters[AMP_3]));
                operators[0].setFm((operators[1].currentSample * localParameters[AMP_1]));
                
                sample = operators[0].currentSample * localParameters[AMP_0];
            }
            else
                clearCurrentNote();
            break;
        case 3:
            if (operators[0].isActive())
            {
                operators[2].setFm(0.0);
                operators[1].setFm(operators[2].currentSample * localParameters[AMP_2]);
                operators[0].setFm((operators[1].currentSample * localParameters[AMP_1]) +
                                   (operators[3].currentSample * localParameters[AMP_3]));
                
                sample = operators[0].currentSample * localParameters[AMP_0];
            }
            else
                clearCurrentNote();
            break;
        case 4:
            if (operators[0].isActive())
            {
                operators[2].setFm(operators[3].currentSample * localParameters[AMP_3]);
                operators[1].setFm(0.0);
                operators[0].setFm((operators[1].currentSample * localParameters[AMP_1]) +
                                   (operators[2].currentSample * localParameters[AMP_2]));

                sample = operators[0].currentSample * localParameters[AMP_0];
            }
            else
                clearCurrentNote();
            break;
        case 5:
            if (operators[0].isActive() || operators[2].isActive())
            {
                operators[2].setFm(operators[3].currentSample * localParameters[AMP_3]);
                operators[1].setFm(0.0);
                operators[0].setFm(operators[1].currentSample * localParameters[AMP_1]);

                sample = operators[0].currentSample * localParameters[AMP_0] +
                        operators[2].currentSample * localParameters[AMP_2];
            }
            else
                clearCurrentNote();
            break;
        case 6:
            if (operators[0].isActive() || operators[1].isActive() || operators[2].isActive())
            {
                operators[2].setFm(operators[3].currentSample * localParameters[AMP_3]);
                operators[1].setFm(operators[3].currentSample * localParameters[AMP_3]);
                operators[0].setFm(operators[3].currentSample * localParameters[AMP_3]);
                
                sample = operators[0].currentSample * operators[0].currentAmplitude * localParameters[AMP_0] +
                    operators[1].currentSample * localParameters[AMP_1] +
                    operators[2].currentSample * localParameters[AMP_2];
            }
            else
                clearCurrentNote();
            break;
        case 7:
            if (operators[0].isActive() || operators[1].isActive() || operators[2].isActive())
            {
                operators[2].setFm(operators[3].currentSample * localParameters[AMP_3]);
                operators[1].setFm(0.0);
                operators[0].setFm(0.0);
                
                sample = operators[0].currentSample * localParameters[AMP_0] +
                    operators[1].currentSample * localParameters[AMP_1] +
                    operators[2].currentSample * localParameters[AMP_2];
            }
            else
                clearCurrentNote();
            break;
        case 8:
            if (operators[0].isActive() || operators[1].isActive() || operators[2].isActive())
            {
                operators[2].setFm(0.0);
                operators[1].setFm(0.0);
                operators[0].setFm(0.0);
                
                sample = operators[0].currentSample * localParameters[AMP_0] +
                operators[1].currentSample * localParameters[AMP_1] +
                operators[2].currentSample * localParameters[AMP_2] +
                operators[3].currentSample * localParameters[AMP_3];
            }
            else
                clearCurrentNote();
            break;
    }
    return sample;
}

void Wx100SynthVoice::aftertouchChanged (int newAftertouchValue)
{
    
}
bool Wx100SynthVoice::isPlayingChannel (int midiChannel) const
{
    return true;
}

bool Wx100SynthVoice::isVoiceActive() const
{
    return operators[0].isActive();
}

void Wx100SynthVoice::actionListenerCallback (const String &message)
{
    if (message.equalsIgnoreCase("LFO Frequency"))
        lfo.setFrequency(localParameters[LFO_FREQ]);
    else if (message.equalsIgnoreCase("LFO Shape"))
        lfo.setWaveTable(*localLfoShape);
}