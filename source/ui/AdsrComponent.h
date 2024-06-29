//
// Created by robbe on 29/06/2024.
//

#ifndef ADSRCOMPONENT_H
#define ADSRCOMPONENT_H
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_gui_basics/juce_gui_basics.h"

class AdsrComponent: public juce::Component {
public:
    explicit AdsrComponent(juce::AudioProcessorValueTreeState& apvts);
    ~AdsrComponent() override;
    void paint (juce::Graphics& g) override;
    void resized() override;
private:
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;

    void setSliderParams( juce::Slider& slider);
};



#endif //ADSRCOMPONENT_H
