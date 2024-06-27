//
// Created by robbe on 27/06/2024.
//

#ifndef SYNTH_VOICE_H
#define SYNTH_VOICE_H

#include "juce_audio_basics/juce_audio_basics.h"
#include "SynthSound.h"

class SynthVoice: public juce::SynthesiserVoice {
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:

};



#endif //SYNTH_VOICE_H
