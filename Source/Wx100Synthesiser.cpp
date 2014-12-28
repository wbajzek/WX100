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


Wx100SynthVoice::Wx100SynthVoice(float *parameters)
{
    localParameters = parameters;
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
}


bool Wx100SynthVoice::canPlaySound (SynthesiserSound* sound)
{
    return true;
}

void Wx100SynthVoice::startNote (const int midiNoteNumber, const float midiVelocity, SynthesiserSound* /*sound*/, const int currentPitchWheelPosition)
{
    for (int i = 0; i < numOperators; ++i)
    {
        operators[i].setPhase(0.0);
        Adsr adsr;
        adsr.attack = localParameters[ATTACK_1 + i];
        adsr.decay = localParameters[DECAY_1 + i];
        adsr.sustainLevel = localParameters[SUSTAIN_1 + i];
        adsr.release = localParameters[RELEASE_1 + i];
        operators[i].setAdsr(adsr);
        operators[i].trigger(midiVelocity);
    }
    voiceIsActive = true;
}

void Wx100SynthVoice::stopNote (float velocity, const bool allowTailOff)
{
//    note = 0;
//    clearCurrentNote();
}

void Wx100SynthVoice::pitchWheelMoved (const int currentPitchWheelPosition)
{
//    freq = calculateFrequency(currentPitchWheelPosition);
}

void Wx100SynthVoice::controllerMoved (const int controllerNumber, const int newValue)
{
    switch (controllerNumber)
    {
//        case MOD_WHEEL_CONTROL:
//            modWheel = (float)newValue / 3.0 / 127.0;
//            break;
//        default:
//            break;
    }
}

void Wx100SynthVoice::renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    const int numChannels = outputBuffer.getNumChannels();
    Frequency freq = MidiMessage::getMidiNoteInHertz(getCurrentlyPlayingNote());
    bool keyIsDown = isKeyDown();
    while (--numSamples >= 0)
    {
        for (int i = 0; i < numChannels; ++i)
            outputBuffer.addSample(i, startSample, getSample(freq) * 0.25);

        for (int i = 0; i < numOperators; ++i)
            operators[i].tick(keyIsDown);
        ++startSample;
    }
}

Amplitude Wx100SynthVoice::getSample(Frequency freq)
{
    Amplitude sample = 0.0;
    switch (algorithm)
    {
        case 1:
            if (operators[0].isActive())
            {
                operators[0].setFrequency(freq + (freq * localParameters[TUNING_1]));
                for (int i = 3; i > 0; --i)
                {
                    float coarse = localParameters[COARSE_1 + i];
                    float fine = localParameters[TUNING_1 + i];
                    Frequency operatorFrequency = (freq * coarse) + (freq * fine);
                    operators[i].setFrequency(operatorFrequency);
                    if (i == 3)
                        operators[i].setFm(operators[i].currentSample *
                                           operators[i].currentAmplitude *
                                           localParameters[AMP_1 + i] *
                                           localParameters[FEEDBACK_4]);
                    operators[i - 1].setFm(
                                           operators[i].currentSample *
                                           operators[i].currentAmplitude *
                                           localParameters[AMP_1 + i]);
                }
                sample = operators[0].currentSample * operators[0].currentAmplitude * localParameters[AMP_1];
            }
            else
                clearCurrentNote();
            break;
        case 2:
        case 3:
            if (operators[0].isActive())
            {
                operators[0].setFrequency(freq + (freq * localParameters[TUNING_1]));
                Amplitude modulator = 0.0;
                for (int i = 3; i > 0; --i)
                {
                    float coarse = localParameters[COARSE_1 + i];
                    float fine = localParameters[TUNING_1 + i];
                    Frequency operatorFrequency = (freq * coarse) + (freq * fine);
                    operators[i].setFrequency(operatorFrequency);
                    if (i < 3)
                    {
                        modulator = operators[i].currentSample * operators[i].currentAmplitude * localParameters[AMP_1 + i];
                        operators[i - 1].setFm(modulator);                        
                    }
                }
                modulator += operators[3].currentSample *
                             operators[3].currentAmplitude *
                             localParameters[AMP_4] *
                             localParameters[FEEDBACK_4];
                operators[0].setFm(modulator);
                sample = operators[0].currentSample * operators[0].currentAmplitude * localParameters[AMP_1];
            }
            else
                clearCurrentNote();
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            if (operators[0].isActive())
            {
                Amplitude modulator = 0.0;
                operators[0].setFrequency(freq + (freq * localParameters[TUNING_1]));
                for (int i = 1; i < numOperators; ++i)
                {
                    float coarse = localParameters[COARSE_1 + i];
                    float fine = localParameters[TUNING_1 + i];
                    Frequency operatorFrequency = (freq * coarse) + (freq * fine);
                    operators[i].setFrequency(operatorFrequency);
                    modulator += operators[i].currentSample * operators[i].currentAmplitude * localParameters[AMP_1 + i];
                }
                operators[0].setFm(modulator);
                
                sample = operators[0].currentSample * operators[0].currentAmplitude * localParameters[AMP_1];
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
    return operators[0].isActive() && isKeyDown();
}