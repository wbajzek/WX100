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


Wx100SynthVoice::Wx100SynthVoice(float *parameters, int *algorithm)
{
    localParameters = parameters;
    localAlgorithm = algorithm;
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
        adsr.attack = localParameters[ATTACK_0 + i];
        adsr.decay = localParameters[DECAY_0 + i];
        adsr.sustainLevel = localParameters[SUSTAIN_0 + i];
        adsr.release = localParameters[RELEASE_0 + i];
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
    Amplitude sample;
    while (--numSamples >= 0 && getCurrentlyPlayingNote() != -1)
    {
        sample = getSample(freq) * 0.25;
        for (int i = 0; i < numChannels; ++i)
            outputBuffer.addSample(i, startSample, sample);

        for (int i = 0; i < numOperators; ++i)
            operators[i].tick(keyIsDown);
        ++startSample;
    }
}

Amplitude Wx100SynthVoice::getSample(Frequency freq)
{
    Amplitude sample = 0.0;
    for (int i = 0; i < numOperators; ++i)
    {
        operators[i].setFrequency((freq * localParameters[COARSE_0 + i]) +
                                  (freq * localParameters[TUNING_0 + i]));
    }
    // last operator always feeds back
    operators[3].setFm(operators[3].currentSample * localParameters[FEEDBACK_3]);
    switch (*localAlgorithm)
    {
        case 1:
            if (operators[0].isActive())
            {
                operators[2].setFm(operators[3].currentSample * operators[3].currentAmplitude * localParameters[AMP_3]);
                operators[1].setFm(operators[2].currentSample * operators[2].currentAmplitude * localParameters[AMP_2]);
                operators[0].setFm(operators[1].currentSample * operators[1].currentAmplitude * localParameters[AMP_1]);
                
                sample = operators[0].currentSample * operators[0].currentAmplitude * localParameters[AMP_0];
            }
            else
                clearCurrentNote();
            break;
        case 2:
            if (operators[0].isActive())
            {
                operators[2].setFm(0.0);
                operators[1].setFm(operators[2].currentSample * operators[2].currentAmplitude * localParameters[AMP_2] +
                                   (operators[3].currentSample * operators[3].currentAmplitude * localParameters[AMP_3]));
                operators[0].setFm((operators[1].currentSample * operators[1].currentAmplitude * localParameters[AMP_1]));
                
                sample = operators[0].currentSample * operators[0].currentAmplitude * localParameters[AMP_0];
            }
            else
                clearCurrentNote();
            break;
        case 3:
            if (operators[0].isActive())
            {
                operators[2].setFm(0.0);
                operators[1].setFm(operators[2].currentSample * operators[2].currentAmplitude * localParameters[AMP_2]);
                operators[0].setFm((operators[1].currentSample * operators[1].currentAmplitude * localParameters[AMP_1]) +
                                   (operators[3].currentSample * operators[3].currentAmplitude * localParameters[AMP_3]));
                
                sample = operators[0].currentSample * operators[0].currentAmplitude * localParameters[AMP_0];
            }
            else
                clearCurrentNote();
            break;
        case 4:
            if (operators[0].isActive())
            {
                operators[2].setFm(operators[3].currentSample * operators[3].currentAmplitude * localParameters[AMP_3]);
                operators[1].setFm(0.0);
                operators[0].setFm((operators[1].currentSample * operators[1].currentAmplitude * localParameters[AMP_1]) +
                                   (operators[2].currentSample * operators[2].currentAmplitude * localParameters[AMP_2]));

                sample = operators[0].currentSample * operators[0].currentAmplitude * localParameters[AMP_0];
            }
            else
                clearCurrentNote();
            break;
        case 5:
            if (operators[0].isActive() || operators[2].isActive())
            {
                operators[2].setFm(operators[3].currentSample * operators[3].currentAmplitude * localParameters[AMP_3]);
                operators[1].setFm(0.0);
                operators[0].setFm(operators[1].currentSample * operators[1].currentAmplitude * localParameters[AMP_1]);

                sample = operators[0].currentSample * operators[0].currentAmplitude * localParameters[AMP_0] +
                        operators[2].currentSample * operators[2].currentAmplitude * localParameters[AMP_2];
            }
            else
                clearCurrentNote();
            break;
        case 6:
            if (operators[0].isActive() || operators[1].isActive() || operators[2].isActive())
            {
                operators[2].setFm(operators[3].currentSample * operators[3].currentAmplitude * localParameters[AMP_3]);
                operators[1].setFm(operators[3].currentSample * operators[3].currentAmplitude * localParameters[AMP_3]);
                operators[0].setFm(operators[3].currentSample * operators[3].currentAmplitude * localParameters[AMP_3]);
                
                sample = operators[0].currentSample * operators[0].currentAmplitude * localParameters[AMP_0] +
                    operators[1].currentSample * operators[1].currentAmplitude * localParameters[AMP_1] +
                    operators[2].currentSample * operators[2].currentAmplitude * localParameters[AMP_2];
            }
            else
                clearCurrentNote();
            break;
        case 7:
            if (operators[0].isActive() || operators[1].isActive() || operators[2].isActive())
            {
                operators[2].setFm(operators[3].currentSample * operators[3].currentAmplitude * localParameters[AMP_3]);
                operators[1].setFm(0.0);
                operators[0].setFm(0.0);
                
                sample = operators[0].currentSample * operators[0].currentAmplitude * localParameters[AMP_0] +
                    operators[1].currentSample * operators[1].currentAmplitude * localParameters[AMP_1] +
                    operators[2].currentSample * operators[2].currentAmplitude * localParameters[AMP_2];
            }
            else
                clearCurrentNote();
            break;
        case 8:
            if (operators[0].isActive() || operators[1].isActive() || operators[2].isActive())
            {
                operators[1].setFm(0.0);
                operators[1].setFm(0.0);
                operators[0].setFm(0.0);
                
                sample = operators[0].currentSample * operators[0].currentAmplitude * localParameters[AMP_0] +
                operators[1].currentSample * operators[1].currentAmplitude * localParameters[AMP_1] +
                operators[2].currentSample * operators[2].currentAmplitude * localParameters[AMP_2] +
                operators[3].currentSample * operators[3].currentAmplitude * localParameters[AMP_3];
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

void Wx100SynthVoice::actionListenerCallback (const String &message)
{
}