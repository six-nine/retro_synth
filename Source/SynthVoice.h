#pragma once

#include <JuceHeader.h>

#include "SyntSound.h"
#include "Data/ADSRData.h"
#include "Data/OscillatorData.h"

class SynthVoice : public juce::SynthesiserVoice{
public:
    bool canPlaySound(juce::SynthesiserSound *) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

    void pitchWheelMoved(int newPitchWheelValue) override;
    
    void update(const float attack, const float decay, const float sustain, const float release);
    
    OscillatorData& getOscillator() { return oscillator; }
    
private:
    ADSRData adsr;
    juce::AudioBuffer<float> synthBuffer;
    OscillatorData oscillator;
    juce::dsp::Gain<float> gain;
    bool prepared = false;
};
