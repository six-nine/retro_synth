/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/ADSRComponent.h"
#include "UI/OscillatorComponent.h"

//==============================================================================
/**
*/
class RetroSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    RetroSynthAudioProcessorEditor (RetroSynthAudioProcessor&);
    ~RetroSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    RetroSynthAudioProcessor& audioProcessor;
    OscillatorComponent oscillator;
    ADSRComponent adsr;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RetroSynthAudioProcessorEditor)
};
