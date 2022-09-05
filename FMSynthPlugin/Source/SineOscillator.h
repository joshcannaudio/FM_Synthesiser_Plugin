/*
  ==============================================================================

    SineOscillator.h
    Created: 3 Sep 2022 1:49:34am
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <cmath>

class SineOscillator {
public:
    /** Contructor */
    SineOscillator();
    
    /** Destructor */
    ~SineOscillator();
    
    /** Gets next sample */
    float nextSample();
    
    /** Updates oscillator frequency */
    void setFrequency(float freq);
    
    /** Returns the current frequency */
    const float getFrequency();
    
    /** Sets current sample rate and updates the phase increment */
    void updateSampleRate(float newSampleRate);
    
    /** Renders a Sine Wave */
    float renderWaveShape(float phase);
    
private:
    void updatePhaseIncrement();
    
    float phasePosition = 0.f;
    float phaseIncrement = 0.f;
    float currentSampleRate = 44100.f;
    
    float frequency;
};
