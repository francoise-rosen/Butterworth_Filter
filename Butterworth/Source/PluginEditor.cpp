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
