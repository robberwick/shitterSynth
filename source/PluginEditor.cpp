#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p), adsr (processorRef.apvts)
{
    juce::ignoreUnused (processorRef);

    addAndMakeVisible (inspectButton);

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

    // make adsr component visible
    addAndMakeVisible (adsr);

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

    g.setColour (juce::Colours::white);
}

void PluginEditor::resized()
{
    // layout the positions of your child components here
    auto bounds = getLocalBounds().reduced (10);
    auto header = bounds.removeFromTop (50);
    auto footer = bounds.removeFromBottom (50);
    adsr.setBounds (bounds);
    inspectButton.setBounds (header.withSizeKeepingCentre (100, 50));

    // set adsr component bounds

}
