/*
  ==============================================================================

    ADSRData.h
    Created: 29 May 2021 10:47:11pm
    Author:  Вадим Козлов

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ADSRData : public juce::ADSR {
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
private:
    juce::ADSR::Parameters adsrParams;
};
