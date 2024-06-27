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
    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    juce::dsp::Oscillator<float> osc { [] (const float x) { return std::sin (x); } };
    juce::dsp::Gain<float> gain;

    bool isPrepared { false };

};



#endif //SYNTH_VOICE_H
