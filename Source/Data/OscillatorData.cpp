#include "OscillatorData.h"

void OscillatorData::setWaveType(const int waveId) {
    if (waveId == 0){
        // sin wave
        initialise([](float x){ return std::sin(x); });
    } else if (waveId == 1){
        // saw wave
        initialise([](float x){ return x / juce::MathConstants<float>::pi; });
    } else if (waveId == 2){
        // square wave
        initialise([](float x){ return x < 0.0f ? -1.0f : 1.0f; });
    }
}

void OscillatorData::prepareToPlay(juce::dsp::ProcessSpec &processSpec) { 
    prepare(processSpec);
    fmOscillator.prepare(processSpec);
}

void OscillatorData::processNextBlock(juce::dsp::AudioBlock<float> &audioBlock) {
    for (int channel = 0; channel < audioBlock.getNumChannels(); channel++){
        for (int sample = 0; sample < audioBlock.getNumSamples(); sample++){
            fmModulation = fmOscillator.processSample(audioBlock.getSample(channel, sample)) * fmDepth;
        }
    }
    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void OscillatorData::setWaveFrequency(int midiNoteNumber){
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmModulation);
    lastMidiNotePlayed = midiNoteNumber;
}

void OscillatorData::setFmParameters(float depth, float frequency){
    fmOscillator.setFrequency(frequency);
    fmDepth = depth;
    setFrequency(std::fabs(juce::MidiMessage::getMidiNoteInHertz(lastMidiNotePlayed) + fmModulation));
}

