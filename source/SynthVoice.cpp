//
// Created by robbe on 27/06/2024.
//

#include "SynthVoice.h"
bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}
void SynthVoice::startNote (const int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setFrequency (juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber));
    adsr.noteOn();
}
void SynthVoice::stopNote (float velocity, const bool allowTailOff)
{
    adsr.noteOff();
    if (! allowTailOff || ! adsr.isActive()) {
        clearCurrentNote();
    }
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

    adsrParams.attack = 0.8f;
    adsrParams.decay = 0.8f;
    adsrParams.sustain = 1.0f;
    adsrParams.release = 1.5f;
    adsr.setParameters (adsrParams);

    isPrepared = true;
}
void SynthVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert (isPrepared);

    // if the voice is not active, return
    if (! isVoiceActive()) {
        return;
    }

    synthBuffer.setSize (outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();


    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    const juce::dsp::ProcessContextReplacing<float> context {audioBlock};
    osc.process (context);
    gain.process (context);
    adsr.applyEnvelopeToBuffer (synthBuffer, 0, synthBuffer.getNumSamples());

    // add the synthBuffer to the outputBuffer
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
        outputBuffer.addFrom (channel, startSample, synthBuffer, channel, 0, numSamples);
        if (! adsr.isActive()) {
            clearCurrentNote();
        }
    }
}