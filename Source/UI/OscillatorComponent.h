#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscillatorComponent  : public juce::Component
{
public:
    OscillatorComponent(juce::AudioProcessorValueTreeState &apvts);
    ~OscillatorComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscillatorWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscillatorWaveSelectorAttachment;
    
    juce::Slider fmFrequencySlider;
    juce::Slider fmDepthSlider;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFrequencySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmDepthSliderAttachment;
    
    juce::Label fmFrequencyLabel {"FM Frequency", "FM Frequency"};
    juce::Label fmDepthLabel {"FM Depth", "FM Depth"};
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    void setSliderWithLabel(juce::Slider &slider,
                            juce::Label &label,
                            juce::String sliderId,
                            std::unique_ptr<SliderAttachment>& attachment,
                            juce::AudioProcessorValueTreeState &apvts);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorComponent)
};
