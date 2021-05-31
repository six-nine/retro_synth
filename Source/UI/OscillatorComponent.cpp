/*
  ==============================================================================

    OscillatorComponent.cpp
    Created: 30 May 2021 12:53:57pm
    Author:  Вадим Козлов

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorComponent.h"

//==============================================================================
OscillatorComponent::OscillatorComponent(juce::AudioProcessorValueTreeState &apvts) {
    juce::StringArray choices { "Sin", "Saw", "Square" };
    oscillatorWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscillatorWaveSelector);
    
    oscillatorWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "OSCILLATORWAVETYPE", oscillatorWaveSelector);
}

OscillatorComponent::~OscillatorComponent()
{
}

void OscillatorComponent::paint (juce::Graphics& g) {
    g.fillAll(juce::Colours::yellow);
}

void OscillatorComponent::resized() {
    oscillatorWaveSelector.setBounds(0, 0, 90, 20);
}
