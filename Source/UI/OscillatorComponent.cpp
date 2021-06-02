#include <JuceHeader.h>
#include "OscillatorComponent.h"

//==============================================================================
OscillatorComponent::OscillatorComponent(juce::AudioProcessorValueTreeState &apvts) {
    juce::StringArray choices { "Sin", "Saw", "Square" };
    oscillatorWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscillatorWaveSelector);
    
    oscillatorWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "OSCILLATORWAVETYPE", oscillatorWaveSelector);
    
    setSliderWithLabel(fmFrequencySlider, fmFrequencyLabel, "FM_FREQUENCY", fmFrequencySliderAttachment, apvts);
    setSliderWithLabel(fmDepthSlider, fmDepthLabel, "FM_DEPTH", fmDepthSliderAttachment, apvts);
}

OscillatorComponent::~OscillatorComponent()
{
}

void OscillatorComponent::paint (juce::Graphics& g) {
    g.fillAll(juce::Colour(41, 41, 41));
}

void OscillatorComponent::resized() {
    int marginTop = 60;
    int padding = 10;
    auto bounds = getLocalBounds();
    int sliderWidth = (bounds.getWidth() - 2 * padding) / 2;
    oscillatorWaveSelector.setBounds(padding, padding, 80, 20);
    
    fmFrequencySlider.setBounds(padding, marginTop, sliderWidth, sliderWidth);
    fmFrequencyLabel.setBounds(fmFrequencySlider.getX(), fmFrequencySlider.getY() - 20, fmFrequencySlider.getWidth(), 20);
    
    fmDepthSlider.setBounds(fmFrequencySlider.getX() + fmFrequencySlider.getWidth() + padding,
                            marginTop,
                            sliderWidth,
                            sliderWidth);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - 20, fmDepthSlider.getWidth(), 20);
}

void OscillatorComponent::setSliderWithLabel(juce::Slider &slider,
                                             juce::Label &label,
                                             juce::String sliderId,
                                             std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> &attachment,
                                             juce::AudioProcessorValueTreeState &apvts){
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, sliderId, slider);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(12.0f);
    addAndMakeVisible(label);
}
