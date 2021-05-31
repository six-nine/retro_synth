/*
  ==============================================================================

    OscillatorData.h
    Created: 30 May 2021 12:25:54pm
    Author:  Вадим Козлов

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscillatorData : public juce::dsp::Oscillator<float>{
public:
    void setWaveType(const int waveId);
    void prepareToPlay(juce::dsp::ProcessSpec &processSpec);
    void setWaveFrequency(int midiNoteNumber);
    void processNextBlock(juce::dsp::AudioBlock<float>& audioBlock);
private:
    
};
