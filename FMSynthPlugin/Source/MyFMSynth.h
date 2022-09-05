/*
  ==============================================================================

    MyFMSynth.h
    Created: 3 Sep 2022 10:21:03am
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include "MyOperator.h"

class MyFMSynth {
public:
    /** Constructor */
    MyFMSynth();
    
    /** Destructor */
    ~MyFMSynth();
    
    void updateSampleRate(float sampleRate);
    
    /** Resets oscillators*/
    void reset();
    
    /** Manipulates frequency so that it can be tuned in semitones */
    float getCoarseTune(float frequency, float coarse); // +- 1 for +- Octave
    
    /** Sets the frequency */
    void setFrequency(float freq);
    
    /** Sets all other parameters of FM*/
    void setFM(float fIndex, float fOscGain[4], float fEnv[4], float fOscTune[4]); //setFM

    /** gets the next sample.
        @return the next sample*/
    float nextSample();
    
private:
    MyOperator modulator[3], carrier;
    float fModulator[3], fCarrier, fOut;
    float fFrequency;
};
