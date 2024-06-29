//
// Created by robbe on 27/06/2024.
//

#ifndef SYNTH_VOICE_H
#define SYNTH_VOICE_H

#include "SynthSound.h"
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_dsp/juce_dsp.h"

class SynthVoice: public juce::SynthesiserVoice {
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void updateADSR (float attack, float decay, float sustain, float release);
    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;

    juce::AudioBuffer<float> synthBuffer;

    juce::dsp::Oscillator<float> osc { [] (const float x) { return x / juce::MathConstants<float>::pi; } };
    juce::dsp::Gain<float> gain;

    bool isPrepared { false };

    // return std::sin (x); // sine wave
    // return x / MathConstants<float>::pi; // saw wave
    // return x < 0.0f ? -1.0f : 1.0f; // square wave
};



#endif //SYNTH_VOICE_H
