/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Butterworth.h"

//==============================================================================
/**
*/
namespace ParamData
{
    /** Class that keeps the name and ID of a parameter. */
    class Parameter
    {
    public:
        Parameter (const juce::String parameterName)
        :paramName {parameterName}
        {
            paramID = paramName + "ID";
        }
        juce::String getName() const
        {
            return paramName;
        }
        juce::String getID() const
        {
            return paramID;
        }
        
    private:
        juce::String paramName;
        juce::String paramID;
        
    };
    
    enum {freq, amount, gain, algo, order};
    const static std::vector<Parameter> paramArray {Parameter{"Frequency"}, Parameter{"Amount"}, Parameter{"Gain"}, Parameter{"Algorithm"}, Parameter{"Order"}};

}

class ButterworthAudioProcessor  : public AudioProcessor,
                                   public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    ButterworthAudioProcessor();
    ~ButterworthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    juce::AudioProcessorValueTreeState& getValueTree();
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    //==============================================================================
    // Listener method(s)
    void parameterChanged (const juce::String& paramID, float newValue) override;
    //==============================================================================
private:
    std::atomic<double> freqAtom, amountAtom, gainAtom;
    std::atomic<int> algorithmAtom, orderAtom;
    juce::OwnedArray<syfo::Butterworth<double>> stereoFilter;
    syfo::FilterParameters<double> filterParameters;
    juce::AudioProcessorValueTreeState parameters;
    
    static constexpr float min_freq {10.0f};
    static constexpr float max_freq {19000.0f};
    static constexpr float min_gain {-100.0f};
    static constexpr float max_gain {24.0f};
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ButterworthAudioProcessor)
};
