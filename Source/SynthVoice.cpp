#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound * sound) {
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) {
    oscillator.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowailOff) {
    adsr.noteOff();
    
    if (!allowailOff || !adsr.isActive()) clearCurrentNote();
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels){
    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec processSpec;
    processSpec.maximumBlockSize = samplesPerBlock;
    processSpec.sampleRate = sampleRate;
    processSpec.numChannels = outputChannels;
    
    oscillator.prepareToPlay(processSpec);
    gain.prepare(processSpec);
    
    gain.setGainLinear(0.3f);
    
    prepared = true;
}

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release) {
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
    jassert(prepared);
    
    if (!isVoiceActive()) return;
    
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> audioBlock = synthBuffer;
    oscillator.processNextBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    
    for (int i = 0; i < outputBuffer.getNumChannels(); i++){
        outputBuffer.addFrom(i, startSample, synthBuffer, i, 0, numSamples);
        if (!adsr.isActive()) clearCurrentNote();
    }
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {
    
}
