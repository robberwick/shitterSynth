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
    gainAttachment = std::make_unique<SliderAttachment> (processorRef.apvts, "GAIN", gainSlider);
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
    auto area = getLocalBounds().reduced (10);
    area.removeFromBottom (50);
    inspectButton.setBounds (getLocalBounds().withSizeKeepingCentre (100, 50));

    constexpr auto padding = 10;
    const auto sliderWidth = area.getWidth() / 5 - (2 * padding);
    const auto sliderHeight = area.getHeight() - (2 * padding);
    constexpr auto sliderStartX = padding;
    const auto sliderStartY = area.getHeight() / 2 - (sliderHeight / 2);

    attackSlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds (attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds (decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds (sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

    gainSlider.setBounds (releaseSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

}
void PluginEditor::setSliderParams (juce::Slider& slider)
{
    slider.setSliderStyle (juce::Slider::LinearVertical);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible (slider);
}
