//
// Created by robbe on 29/06/2024.
//

#ifndef ADSRDATA_H
#define ADSRDATA_H
#pragma once

#include "juce_audio_basics/juce_audio_basics.h"

class AdsrData : public juce::ADSR
{
public:
    void updateADSR (float attack, float decay, float sustain, float release);

private:
    Parameters adsrParams;
};

#endif //ADSRDATA_H
