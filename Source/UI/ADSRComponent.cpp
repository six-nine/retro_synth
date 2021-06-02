#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent(juce::AudioProcessorValueTreeState &apvts) {
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);
    
    setSliderParameters(attackSlider);
    setSliderParameters(decaySlider);
    setSliderParameters(sustainSlider);
    setSliderParameters(releaseSlider);
}

ADSRComponent::~ADSRComponent(){
    attackAttachment.reset();
    decayAttachment.reset();
    sustainAttachment.reset();
    releaseAttachment.reset();
}

void ADSRComponent::paint (juce::Graphics& g) {
    g.fillAll(juce::Colour(41, 41, 41));
}

void ADSRComponent::resized() {
    const auto padding = 10;
    const auto bounds = getLocalBounds();
    const auto sliderWidth = (bounds.getWidth() - padding * 5) / 4;
    const auto sliderHeight  = bounds.getHeight() - 2 * padding;
    const auto sliderStartX = padding;
    const auto sliderStartY = padding;
    
    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

void ADSRComponent::setSliderParameters(juce::Slider &slider){
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
