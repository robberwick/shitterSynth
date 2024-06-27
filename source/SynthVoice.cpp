//
// Created by robbe on 27/06/2024.
//

#include "SynthVoice.h"
bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}
void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setFrequency (juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber));
    adsr.noteOn();
}
void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
}
void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
}
void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
}
void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);

    adsr.setSampleRate (sampleRate);

    juce::dsp::ProcessSpec spec {};
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;

    osc.prepare (spec);
    gain.prepare (spec);

    gain.setGainLinear (0.1f);

    isPrepared = true;
}
void SynthVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert (isPrepared);
    juce::dsp::AudioBlock<float> audioBlock { outputBuffer };
    const juce::dsp::ProcessContextReplacing<float> context {audioBlock};
    osc.process (context);
    gain.process (context);
    adsr.applyEnvelopeToBuffer (outputBuffer, startSample, numSamples);
}