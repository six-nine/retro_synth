/*
  ==============================================================================

    ADSRData.cpp
    Created: 29 May 2021 10:47:11pm
    Author:  Вадим Козлов

  ==============================================================================
*/

#include "ADSRData.h"

void ADSRData::updateADSR(const float attack, const float decay, const float sustain, const float release){
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    
    setParameters(adsrParams);
}
