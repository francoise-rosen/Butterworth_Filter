/*
  ==============================================================================

    N-order Butterworth filter using Cascade

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
    /** GUI objects. */
    juce::Slider frequencySlider, gainSlider, amountSlider;
    juce::ComboBox algorithmCombo, orderCombo;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    std::unique_ptr<SliderAttachment> frequencySliderAttachment, gainSliderAttachment, amountSliderAttachment;
    std::unique_ptr<ComboBoxAttachment> algorithmComboAttachment, orderComboAttachment;
    
    void fillCombos ();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ButterworthAudioProcessorEditor)
};
