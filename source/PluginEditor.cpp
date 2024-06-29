#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    addAndMakeVisible (inspectButton);
    attackAttachment = std::make_unique<SliderAttachment> (processorRef.apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment> (processorRef.apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment> (processorRef.apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment> (processorRef.apvts, "RELEASE", releaseSlider);
    oscAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (processorRef.apvts, "OSC", oscSelector);

    // this chunk of code instantiates and opens the melatonin inspector
    inspectButton.onClick = [&] {
        if (!inspector)
        {
            inspector = std::make_unique<melatonin::Inspector> (*this);
            inspector->onClose = [this]() { inspector.reset(); };
        }

        inspector->setVisible (true);
    };

    setSliderParams (attackSlider);
    setSliderParams (decaySlider);
    setSliderParams (sustainSlider);
    setSliderParams (releaseSlider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

PluginEditor::~PluginEditor()
{
}

void PluginEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    auto area = getLocalBounds();
    g.setColour (juce::Colours::white);
    g.setFont (16.0f);
    // auto helloWorld = juce::String ("Hello from ") + PRODUCT_NAME_WITHOUT_VERSION + " v" VERSION + " running in " + CMAKE_BUILD_TYPE;
    // g.drawText (helloWorld, area.removeFromTop (150), juce::Justification::centred, false);
}

void PluginEditor::resized()
{
    // layout the positions of your child components here
    auto bounds = getLocalBounds().reduced (10);
    auto header = bounds.removeFromTop (50);
    auto footer = bounds.removeFromBottom (50);
    auto oscSelectorBounds = bounds;
    inspectButton.setBounds (header.withSizeKeepingCentre (100, 50));

    constexpr auto padding = 10;
    const auto sliderWidth = oscSelectorBounds.getWidth() / 4;
    const auto sliderHeight = oscSelectorBounds.getHeight() - (padding);
    const auto sliderStartX = oscSelectorBounds.getX();
    const auto sliderStartY = oscSelectorBounds.getHeight() / 2 - (sliderHeight / 2);

    attackSlider.setBounds (oscSelectorBounds.removeFromLeft (sliderWidth));
    decaySlider.setBounds (oscSelectorBounds.removeFromLeft (sliderWidth));
    sustainSlider.setBounds (oscSelectorBounds.removeFromLeft (sliderWidth));
    releaseSlider.setBounds (oscSelectorBounds.removeFromLeft (sliderWidth));

}
void PluginEditor::setSliderParams (juce::Slider& slider)
{
    slider.setSliderStyle (juce::Slider::LinearVertical);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible (slider);
}
