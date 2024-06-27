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
}
void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
}
void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
}
void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
}
void SynthVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
}