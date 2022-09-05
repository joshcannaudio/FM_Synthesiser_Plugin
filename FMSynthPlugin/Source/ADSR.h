/*
  ==============================================================================

    ADSR.h
    Created: 3 Sep 2022 2:15:01am
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once

class MyEnvelope {
public:
    /** Consructor */
    MyEnvelope();
    
    /** Updates the sample rate */
    void updateSampleRate(float sampleRate); // make it static?
    
    /** Sets the ADSR and converts the variables into increments per sample */
    void setADSR(float attack, float decay, float sustain, float release = 0);
    
    /** Sets the AHDSR and converts the variables into increments per sample */
    void setAHDSR(float attack, float hold, float decay, float sustain, float release);
    
    /** Changes the state of STAGE to release - Should be called when when a note off message is recieved */
    void release();
    
    /** Runs the envelope */
    float tick();
    
    /** Keeps track of the stage using switch case in tick() */
    enum STAGE {
        ATTACK,
        HOLD,
        DECAY,
        SUSTAIN,
        RELEASE,
        OFF
    };
    
    /** Returns the stage to enable the voice to be released */
    STAGE getStage();
    
    
    float getRelease() { return releaseTime; }
    
private:
    float attack_, hold_, decay_, sustain_, release_, releaseTime;
    float amplitude, rampMult, holdCount;
    float currentSampleRate = 48000.f;
    STAGE stage;
    float inv(float val) { return 1.0 / val; }
};

