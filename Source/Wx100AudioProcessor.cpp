/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "Wx100AudioProcessor.h"
#include "Wx100Editor.h"

//==============================================================================
Wx100AudioProcessor::Wx100AudioProcessor()
{
    for (int i = 0; i < numOperators; ++i)
    {
        parameters[AMP_0 + i] = 0.0;
        parameters[COARSE_0 + i] = 1.0;
        parameters[TUNING_0 + i] = 0.0;
        parameters[ATTACK_0 + i] = 0.0;
        parameters[DECAY_0 + i] = 0.0;
        parameters[SUSTAIN_0 + i] = 1.0;
        parameters[RELEASE_0 + i] = 0.0;
    }
    parameters[AMP_0] = 1.0;
    parameters[FEEDBACK_3] = 0.0;
    parameters[LFO_AMP_AMOUNT] = 0.0;
    parameters[LFO_PITCH_AMOUNT] = 0.0;
    parameters[LFO_FREQ] = 7.0;
    parameters[LFO_INIT_PHASE] = 0.0;
    lfoShape = SINE_WAVE_TABLE;
    algorithm = 1;
    scale = 1;
    scaleRoot = 1;
    
    initAllParameters();

    synth.addSound(new Wx100SynthSound());
    for (int i = 0; i < 16; ++i)
    {
        Wx100SynthVoice *voice = new Wx100SynthVoice(parameters, &algorithm, &lfoShape, &scale, &scaleRoot);
        addActionListener(voice);
        synth.addVoice(voice);
    }
    sendActionMessage("LFO Frequency");
    sendActionMessage("LFO Shape");
    synth.setNoteStealingEnabled(true);
}

Wx100AudioProcessor::~Wx100AudioProcessor()
{
}

void Wx100AudioProcessor::initParameters()
{
    for (int i = 0; i < numOperators; ++i)
    {
        char ampName[30];
        sprintf(ampName, "Amp_%i", i + 1);
        addFloatParam(AMP_0 + i, ampName, true, SAVE, &parameters[AMP_0 + i], 0.00, 1.0);
    }
    
    for (int i = 0; i < numOperators; ++i)
    {
        char coarseName[30];
        sprintf(coarseName, "Coarse_%i", i + 1);
        addFloatParam(COARSE_0 + i, coarseName, true, SAVE, &parameters[COARSE_0 + i], 1.00, 10.0);
    }
    
    for (int i = 0; i < numOperators; ++i)
    {
        char tuningName[30];
        sprintf(tuningName, "Tuning_%i", i + 1);
        addFloatParam(TUNING_0 + i, tuningName, true, SAVE, &parameters[TUNING_0 + i], -1.00, 1.0);
    }
    
    for (int i = 0; i < numOperators; ++i)
    {
        char attackName[30];
        sprintf(attackName, "Attack_%i", i + 1);
        addFloatParam(ATTACK_0 + i, attackName, true, SAVE, &parameters[ATTACK_0 + i], 0.001, 10.0);
    }
    
    for (int i = 0; i < numOperators; ++i)
    {
        char decayName[30];
        sprintf(decayName, "Decay_%i", i + 1);
        addFloatParam(DECAY_0 + i, decayName, true, SAVE, &parameters[DECAY_0 + i], 0.001, 10.0);
    }
    
    for (int i = 0; i < numOperators; ++i)
    {
        char sustainName[30];
        sprintf(sustainName, "Sustain_%i", i + 1);
        addFloatParam(SUSTAIN_0 + i, sustainName, true, SAVE, &parameters[SUSTAIN_0 + i], 0.00, 1.0);
    }
    
    for (int i = 0; i < numOperators; ++i)
    {
        char releaseName[30];
        sprintf(releaseName, "Release_%i", i + 1);
        addFloatParam(RELEASE_0 + i, releaseName, true, SAVE, &parameters[RELEASE_0 + i], 0.001, 10.0);
    }

    char feedbackName[30];
    sprintf(feedbackName, "Feedback_%i", 4);
    addFloatParam(FEEDBACK_3, feedbackName, true, SAVE, &parameters[FEEDBACK_3], 0.0, 1.0);

    addIntParam(ALGORITHM, "Algorithm", true, SAVE, &algorithm, 1, 8);
    addIntParam(SCALE, "Scale", true, SAVE, &scale, 1, numberOfScales+1);
    addIntParam(SCALE_ROOT, "Scale_Root", true, SAVE, &scaleRoot, 1, 12);
    addFloatParam(LFO_FREQ, "Lfo_Frequency", true, SAVE, &parameters[LFO_FREQ], 0.0, 100.0);
    addIntParam(LFO_SHAPE, "Lfo_Shape", true, SAVE, &lfoShape, SINE_WAVE_TABLE, NUMBER_OF_WAVE_TABLES);
    addFloatParam(LFO_AMP_AMOUNT, "Lfo_Amp_Amount", true, SAVE, &parameters[LFO_AMP_AMOUNT], 0.0, 1.0);
    addFloatParam(LFO_PITCH_AMOUNT, "Lfo_Pitch_Amount", true, SAVE, &parameters[LFO_PITCH_AMOUNT], 0.0, 1.0);
    addFloatParam(LFO_INIT_PHASE, "Lfo_Init_Phase", true, SAVE, &parameters[LFO_INIT_PHASE], 0.0, 1.0);
}

const String Wx100AudioProcessor::getParameterText (int index)
{
    return String();
}

const String Wx100AudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String Wx100AudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool Wx100AudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool Wx100AudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

double Wx100AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Wx100AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Wx100AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Wx100AudioProcessor::setCurrentProgram (int index)
{
}

const String Wx100AudioProcessor::getProgramName (int index)
{
    return String();
}

void Wx100AudioProcessor::changeProgramName (int index, const String& newName)
{
}


void Wx100AudioProcessor::runAfterParamChange(int paramIndex,UpdateFromFlags updateFromFlag)
{
    getParam(paramIndex)->updateHostAndUi(false,UPDATE_FROM_PROCESSOR);
    switch (paramIndex) {
        case LFO_FREQ:
            sendActionMessage("LFO Frequency");
            break;
        case LFO_SHAPE:
            sendActionMessage("LFO Shape");
            break;
    }
}

void Wx100AudioProcessor::runAfterParamGroupUpdate()
{
    for (int i = 0; i < NUMBER_OF_PARAMETERS; ++i)
        getParam(AMP_0 + i)->updateHostAndUi(false,UPDATE_FROM_PROCESSOR);
}

//==============================================================================
void Wx100AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void Wx100AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void Wx100AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    buffer.clear();
    int numSamples = buffer.getNumSamples();
    keyboardState.processNextMidiBuffer(midiMessages, 0, numSamples, true);
    synth.renderNextBlock(buffer, midiMessages, 0, numSamples);
}

//==============================================================================
bool Wx100AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Wx100AudioProcessor::createEditor()
{
    return new Wx100AudioProcessorEditor (*this);
}

//==============================================================================
void Wx100AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    //Save all the parameter values into an XML tag with name JucePlugin_Name.
    XmlElement xml(JucePlugin_Name);
    saveXml(&xml,false,true);
    //Save it as binary data
    copyXmlToBinary (xml, destData);
}

void Wx100AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    //Convert the binary data saved in getStateInformation(...) back into XML.
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    // Check that it is valid XML and that the tag has name JucePlugin_Name.
    if (xmlState != 0 && xmlState->getTagName()==JucePlugin_Name){
        //Preload XML values into memory
        readXml(xmlState, true);
        //Update the parameter values from the preloaded XML values
        updateProcessorHostAndUiFromXml(true,true,true);
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Wx100AudioProcessor();
}
