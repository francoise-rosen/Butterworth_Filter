/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "RosenAlphaLookAndFeel_V1.h"

//==============================================================================
/**
*/
class ButterworthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ButterworthAudioProcessorEditor (ButterworthAudioProcessor&);
    ~ButterworthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    ButterworthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ButterworthAudioProcessorEditor)
};
