/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RetroSynthAudioProcessorEditor::RetroSynthAudioProcessorEditor (RetroSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscillator(audioProcessor.apvts), adsr(audioProcessor.apvts) {
    setSize (400, 300);
        
    addAndMakeVisible(adsr);
    addAndMakeVisible(oscillator);
}

RetroSynthAudioProcessorEditor::~RetroSynthAudioProcessorEditor()
{
}

//==============================================================================
void RetroSynthAudioProcessorEditor::paint (juce::Graphics& g) {
    g.fillAll(juce::Colours::red);
}

void RetroSynthAudioProcessorEditor::resized() {
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
    oscillator.setBounds(10, 10, 200, 200);
}


