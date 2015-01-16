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

void Wx100Synthesiser::refreshCurrentPlaybackSampleRate ()
{
    double sampleRate = getSampleRate();

    allNotesOff (0, false);

    for (int i = voices.size(); --i >= 0;)
        voices.getUnchecked (i)->setCurrentPlaybackSampleRate (sampleRate);
}

Wx100SynthVoice::Wx100SynthVoice(float *parameters, int *algorithm, int *lfoShape, int *scaleRoot, Frequency *tuningTable)
{
    localParameters = parameters;
    localAlgorithm = algorithm;
    localScaleRoot = scaleRoot;
    localTuningTable = tuningTable;
    localLfoShape = lfoShape;
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

    while (--numSamples >= 0 && getCurrentlyPlayingNote() != -1)
    {
        lfoLevel = lfo.tick();
        Amplitude sample = getSample(freq + (freq * modWheel * lfoLevel)) * (0.25 + lfoLevel * localParameters[LFO_AMP_AMOUNT]);

        outputBuffer.addSample(0, startSample, sample);

        for (int i = 0; i < numChannels; ++i)
            outputBuffer.addSample(i, startSample, sample);

        lastOp4Samples[1] = lastOp4Samples[0];
        lastOp4Samples[0] = (lastOp4Samples[1] + operators[3].currentSample) * 0.5;
        for (int i = 0; i < numOperators; ++i)
            operators[i].tick();

        ++startSample;
    }
    if (numChannels == 2)
        outputBuffer.copyFrom(1, 0, outputBuffer, 0, 0, startSample);
}

inline Amplitude Wx100SynthVoice::operatorOutput(int i) const
{
    Amplitude temp = operators[i].currentSample * localParameters[AMP_0 + i];
    temp += temp * lfoLevel * localParameters[LFO_AMP_0 + i];
    return temp;
}

Amplitude Wx100SynthVoice::getSample(Frequency freq)
{
    for (int i = 0; i < numOperators; ++i)
    {
        Frequency ratioFreq = freq * localParameters[RATIO_0 + i];
        operators[i].setFrequency(ratioFreq + ratioFreq * detune[i]);
    }

    // last operator always feeds back
    operators[3].setFm((lastOp4Samples[0] + operators[3].currentSample) * 0.5 * localParameters[FEEDBACK_3]);
    switch (*localAlgorithm)
    {
        case 1:
            if (operators[0].isActive())
            {
                operators[2].setFm(operatorOutput(3));
                operators[1].setFm(operatorOutput(2));
                operators[0].setFm(operatorOutput(1));
                
                return operatorOutput(0);
            }
            else
                clearCurrentNote();
            break;
        case 2:
            if (operators[0].isActive())
            {
                operators[2].setFm(0.0);
                operators[1].setFm(operatorOutput(2) +
                                   operatorOutput(3));
                operators[0].setFm(operatorOutput(1));
                
                return operatorOutput(0);
            }
            else
                clearCurrentNote();
            break;
        case 3:
            if (operators[0].isActive())
            {
                operators[2].setFm(0.0);
                operators[1].setFm(operatorOutput(2));
                operators[0].setFm(operatorOutput(1) +
                                   operatorOutput(3));
                
                return operatorOutput(0);
            }
            else
                clearCurrentNote();
            break;
        case 4:
            if (operators[0].isActive())
            {
                operators[2].setFm(operatorOutput(3));
                operators[1].setFm(0.0);
                operators[0].setFm(operatorOutput(1) +
                                   operatorOutput(2));

                return operatorOutput(0);
            }
            else
                clearCurrentNote();
            break;
        case 5:
            if (operators[0].isActive() || operators[2].isActive())
            {
                operators[2].setFm(operatorOutput(3));
                operators[1].setFm(0.0);
                operators[0].setFm(operatorOutput(1));

                return operatorOutput(0) +
                        operatorOutput(2);
            }
            else
                clearCurrentNote();
            break;
        case 6:
            if (operators[0].isActive() || operators[1].isActive() || operators[2].isActive())
            {
                operators[2].setFm(operatorOutput(3));
                operators[1].setFm(operatorOutput(3));
                operators[0].setFm(operatorOutput(3));
                
                return operatorOutput(0) +
                    operatorOutput(1) +
                    operatorOutput(2);
            }
            else
                clearCurrentNote();
            break;
        case 7:
            if (operators[0].isActive() || operators[1].isActive() || operators[2].isActive())
            {
                operators[2].setFm(operatorOutput(3));
                operators[1].setFm(0.0);
                operators[0].setFm(0.0);
                
                return operatorOutput(0) +
                    operatorOutput(1) +
                    operatorOutput(2);
            }
            else
                clearCurrentNote();
            break;
        case 8:
            if (operators[0].isActive() || operators[1].isActive() || operators[2].isActive() || operators[3].isActive())
            {
                operators[2].setFm(0.0);
                operators[1].setFm(0.0);
                operators[0].setFm(0.0);
                
                return operatorOutput(0) +
                    operatorOutput(1) +
                    operatorOutput(2) +
                    operatorOutput(3);
            }
            else
                clearCurrentNote();
            break;
    }
    return 0.0;
}

void Wx100SynthVoice::aftertouchChanged (int newAftertouchValue)
{
    
}

void Wx100SynthVoice::actionListenerCallback (const String &message)
{
    if (message.equalsIgnoreCase("LFO Frequency"))
        lfo.setFrequency(localParameters[LFO_FREQ]);
    else if (message.equalsIgnoreCase("LFO Shape"))
        lfo.setWaveTable(*localLfoShape);
    else if (message.equalsIgnoreCase("Detune"))
        for (int i = 0; i < numOperators; ++i)
            detune[i] = pow(2.0, localParameters[TUNING_0 + i] * 0.25); // 0.25 for reasonable range
}