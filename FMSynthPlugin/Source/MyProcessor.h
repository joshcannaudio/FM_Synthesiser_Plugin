/*
  ==============================================================================

    MyProcessor.h
    Created: 9 Aug 2022 11:24:53am
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Effects.h"

class MyProcessor {
public:
    MyProcessor();
    
    ~MyProcessor();
    
    void prepareToPlay(float currentSampleRate);
    
    void process(const float *pfInBuffer0, const float *pfInBuffer1, float *pfOutBuffer0, float *pfOutBuffer1, int numSamples, AudioProcessorValueTreeState& apvts);
    
private:
    Distortion distortion;
    MyModulation tremelo;
};

