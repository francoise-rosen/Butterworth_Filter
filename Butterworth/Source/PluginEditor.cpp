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
    fillCombos();
    
    frequencySliderAttachment = std::make_unique<SliderAttachment> (processor.getValueTree(), ParamData::paramArray[ParamData::freq].getID(), frequencySlider);
    amountSliderAttachment = std::make_unique<SliderAttachment> (processor.getValueTree(), ParamData::paramArray[ParamData::amount].getID(), amountSlider);
    gainSliderAttachment = std::make_unique<SliderAttachment> (processor.getValueTree(), ParamData::paramArray[ParamData::gain].getID(), gainSlider);
    algorithmComboAttachment = std::make_unique<ComboBoxAttachment> (processor.getValueTree(), ParamData::paramArray[ParamData::algo].getID(), algorithmCombo);
    orderComboAttachment = std::make_unique<ComboBoxAttachment> (processor.getValueTree(), ParamData::paramArray[ParamData::order].getID(), orderCombo);
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
    auto filterArea = getLocalBounds().reduced (5.0f);
    auto gainArea = filterArea.removeFromRight (getWidth() * 0.33f);
    amountSlider.setBounds(gainArea.removeFromLeft (gainArea.getWidth() * 0.5f));
    gainSlider.setBounds (gainArea);
    
    frequencySlider.setBounds (filterArea.removeFromTop (filterArea.getHeight() * 0.5f));
    algorithmCombo.setBounds (filterArea.removeFromTop (filterArea.getHeight() * 0.5f));
    orderCombo.setBounds (filterArea);
}

void ButterworthAudioProcessorEditor::fillCombos()
{
   algorithmCombo.addItemList (syfo::ButterworthID::butterworthFilterAlgorithmIDs, 100);
   orderCombo.addItemList (syfo::ButterworthID::butterworthFilterOrderIDs, 100);
}
