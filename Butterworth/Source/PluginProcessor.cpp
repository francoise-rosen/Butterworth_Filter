/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ButterworthAudioProcessor::ButterworthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
freqAtom {1000.0}, amountAtom {1.0}, gainAtom {-12.0}, algorithmAtom {0},
orderAtom {2}, filterParameters {freqAtom.load(), algorithmAtom.load(), orderAtom.load()},
parameters {
    *this,
    nullptr,
    juce::Identifier ("Filter_Parameters"),
    createParameterLayout()
}
{
    filterParameters.frequency = freqAtom.load();

}

ButterworthAudioProcessor::~ButterworthAudioProcessor()
{
}

//==============================================================================
void ButterworthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int i = 0; i < getTotalNumInputChannels(); ++i)
    {
        stereoFilter.add (new syfo::Butterworth<double> ());
    }
}

void ButterworthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ButterworthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ButterworthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
const String ButterworthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ButterworthAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool ButterworthAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool ButterworthAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double ButterworthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ButterworthAudioProcessor::getNumPrograms()
{
    return 1;
}

int ButterworthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ButterworthAudioProcessor::setCurrentProgram (int index)
{
}

const String ButterworthAudioProcessor::getProgramName (int index)
{
    return {};
}

void ButterworthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
bool ButterworthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ButterworthAudioProcessor::createEditor()
{
    return new ButterworthAudioProcessorEditor (*this);
}

//==============================================================================
void ButterworthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ButterworthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ButterworthAudioProcessor();
}

juce::AudioProcessorValueTreeState& ButterworthAudioProcessor::getValueTree()
{
    return parameters;
}

juce::AudioProcessorValueTreeState::ParameterLayout ButterworthAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout parameterLayout;
    
    /** Add frequency parameter. */
    parameterLayout.add (std::make_unique<juce::AudioParameterFloat> (ParamData::paramArray[ParamData::freq].getID(),   /* Parameter ID */
         ParamData::paramArray[ParamData::freq].getName(), /* Parameter Name */
         juce::NormalisableRange<float> (min_freq, max_freq, 0.01f, /* Range */
             std::log (0.5f) / std::log (1000.0f / (max_freq - min_freq))),
         static_cast<float> (freqAtom.load()),
         "Hz",
         juce::AudioProcessorParameter::genericParameter,
         [] (float val, int) {return (val < 1000.0f) ? juce::String (val, 2) + "Hz" : juce::String (val / 1000.0f, 2) + "kHz";},
         [] (const juce::String& str_value) {return str_value.dropLastCharacters(3).getFloatValue();}));
    
    /** Add amount parameter. */
    parameterLayout.add (std::make_unique<juce::AudioParameterFloat> (ParamData::paramArray[ParamData::amount].getID(),
         ParamData::paramArray[ParamData::amount].getName(),
         juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f),
         static_cast<float> (amountAtom.load()), juce::String(),
         juce::AudioProcessorParameter::genericParameter, [] (float val, int) {return juce::String (val * 100.0f) + "%";},
         [] (const juce::String& str_value) {return str_value.dropLastCharacters(1).getFloatValue();}));
    
    /** Add gain parameter. */
    parameterLayout.add (std::make_unique<juce::AudioParameterFloat> (ParamData::paramArray[ParamData::gain].getID(), ParamData::paramArray[ParamData::gain].getName(), juce::NormalisableRange<float> (min_gain, max_gain, 0.1f, std::log (0.5f) / std::log (88.0f / (max_gain - min_gain))), static_cast<float> (gainAtom.load()), "dB", juce::AudioProcessorParameter::genericParameter, [] (float val, int) {return (val > -100.0f) ? juce::String (val) + "dB" : "-inf";}, [] (const juce::String& str_val) {return str_val.dropLastCharacters (2).getFloatValue();}));
    
    /** Add Combos. */
    parameterLayout.add (std::make_unique<juce::AudioParameterChoice> (ParamData::paramArray[ParamData::algo].getID(), ParamData::paramArray[ParamData::algo].getName(), syfo::ButterworthID::butterworthFilterAlgorithmIDs, algorithmAtom.load()));
    parameterLayout.add (std::make_unique<juce::AudioParameterChoice> (ParamData::paramArray[ParamData::order].getID(), ParamData::paramArray[ParamData::order].getName(), syfo::ButterworthID::butterworthFilterOrderIDs, orderAtom.load()));
    
    return parameterLayout;
}

//==============================================================================
// Listener
void ButterworthAudioProcessor::parameterChanged (const juce::String &paramID,
                                                 float newValue)
{
    if (paramID == ParamData::paramArray[ParamData::freq].getID())
        freqAtom.store (static_cast<double> (newValue));
    else if (paramID == ParamData::paramArray[ParamData::amount].getID())
        amountAtom.store (static_cast<double> (newValue));
    else if (paramID == ParamData::paramArray[ParamData::gain].getID())
        gainAtom.store (static_cast<double> (newValue));
    else if (paramID == ParamData::paramArray[ParamData::algo].getID())
        algorithmAtom.store (static_cast<int> (newValue));
    else if (paramID == ParamData::paramArray[ParamData::order].getID())
        orderAtom.store (static_cast<int> (newValue));
}
