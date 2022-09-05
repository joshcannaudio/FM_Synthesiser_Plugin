/*
  ==============================================================================

    MyOperator.h
    Created: 3 Sep 2022 10:21:11am
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include "SineOscillator.h"

class MyOperator {
public:
    /** Constrctor */
    MyOperator();
    
    /** Resets the oscillators */
    void reset();
    
    void updateSampleRate(float sampleRate);

    /** Sets the frequency of the oscillators.
     @param fFrequency frequency from note on message */
    void setOscillator(float fFrequency);
    
    /** Sets the modulators */
    void setModulator(float fIndex, float fFrequency);
    
    /** Gets the next sample of the carrier*/
    float tickCarrier();
    
    /** Gets the next sample of the modulator*/
    float tickModulator();
    
    /** Limits the fequency to be below the nyquist limit */
    float blit(float frequency);
    
private:
    float currentSampleRate = 44100.f;
    SineOscillator modulator;
    SineOscillator carrier;
    float fd, I, Ifd, fMod, fc;
};
