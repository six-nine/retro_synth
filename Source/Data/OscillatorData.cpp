/*
  ==============================================================================

    OscillatorData.cpp
    Created: 30 May 2021 12:25:54pm
    Author:  Вадим Козлов

  ==============================================================================
*/

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
}

void OscillatorData::processNextBlock(juce::dsp::AudioBlock<float> &audioBlock) { 
    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void OscillatorData::setWaveFrequency(int midiNoteNumber){
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}


