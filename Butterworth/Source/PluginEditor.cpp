/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ButterworthAudioProcessorEditor::ButterworthAudioProcessorEditor (ButterworthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (400, 300);
    frequencySlider.setSliderStyle (juce::Slider::SliderStyle::Rotary);
    addAndMakeVisible (&frequencySlider);
    amountSlider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    addAndMakeVisible (&amountSlider);
    gainSlider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    addAndMakeVisible (&gainSlider);
    fillAlgorithmCombo (syfo::ButterworthID::butterworthFilterAlgorithmIDs.size());
}

ButterworthAudioProcessorEditor::~ButterworthAudioProcessorEditor()
{
}

//==============================================================================
void ButterworthAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void ButterworthAudioProcessorEditor::resized()
{

}

void ButterworthAudioProcessorEditor::fillAlgorithmCombo (int numFilters)
{
   algorithmCombo.addItemList (syfo::ButterworthID::butterworthFilterAlgorithmIDs, 100);
}
