#pragma once
#include <JuceHeader.h>

class OscillatorData : public juce::dsp::Oscillator<float>{
public:
    void setWaveType(const int waveId);
    void prepareToPlay(juce::dsp::ProcessSpec &processSpec);
    void setWaveFrequency(int midiNoteNumber);
    void processNextBlock(juce::dsp::AudioBlock<float>& audioBlock);
    void setFmParameters(float depth, float frequency);
private:
    juce::dsp::Oscillator<float> fmOscillator{ [](float x){ return std::sin(x); } };
    float fmModulation = 0.0f;
    float fmDepth = 0.0f;
    int lastMidiNotePlayed = 0;
};
