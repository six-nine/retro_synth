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
    setSize (450, 200);
    setResizable(false, false);
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colour(255, 163, 26));
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(128, 128, 128));
    getLookAndFeel().setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(27, 27, 27));
        
    getLookAndFeel().setColour(juce::Slider::trackColourId, juce::Colour(128, 128, 128));
    getLookAndFeel().setColour(juce::Slider::backgroundColourId, juce::Colour(27, 27, 27));
        
    getLookAndFeel().setColour(juce::ComboBox::backgroundColourId, juce::Colour(41, 41, 41));
    getLookAndFeel().setColour(juce::ComboBox::arrowColourId, juce::Colour(255, 163, 26));
    getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId, juce::Colour(41, 41, 41));
    getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colour(27, 27, 27));
        
    addAndMakeVisible(adsr);
    addAndMakeVisible(oscillator);
}

RetroSynthAudioProcessorEditor::~RetroSynthAudioProcessorEditor()
{
}

//==============================================================================
void RetroSynthAudioProcessorEditor::paint (juce::Graphics& g) {
    g.fillAll(juce::Colour(27, 27, 27));
}

void RetroSynthAudioProcessorEditor::resized() {
    adsr.setBounds(getWidth() / 2 + 5, 10, getWidth() / 2 - 15, getHeight() - 20);
    oscillator.setBounds(10, 10, getWidth() / 2 - 15, getHeight() - 20);
}
