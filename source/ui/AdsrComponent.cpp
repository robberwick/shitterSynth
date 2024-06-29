//
// Created by robbe on 29/06/2024.
//

#include "AdsrComponent.h"
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    attackAttachment = std::make_unique<SliderAttachment> (apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment> (apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment> (apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment> (apvts, "RELEASE", releaseSlider);

    setSliderParams (attackSlider);
    setSliderParams (decaySlider);
    setSliderParams (sustainSlider);
    setSliderParams (releaseSlider);
}
AdsrComponent::~AdsrComponent()
{
}
void AdsrComponent::paint (juce::Graphics& g)
{
    Component::paint (g);
    g.fillAll (juce::Colours::black);
}
void AdsrComponent::resized()
{
    Component::resized();
    auto bounds = getLocalBounds().reduced (10);
    const auto sliderWidth = bounds.getWidth() / 4;
    attackSlider.setBounds (bounds.removeFromLeft (sliderWidth));
    decaySlider.setBounds (bounds.removeFromLeft (sliderWidth));
    sustainSlider.setBounds (bounds.removeFromLeft (sliderWidth));
    releaseSlider.setBounds (bounds.removeFromLeft (sliderWidth));
}
void AdsrComponent::setSliderParams (juce::Slider& slider)
{
    slider.setSliderStyle (juce::Slider::LinearVertical);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible (slider);
}