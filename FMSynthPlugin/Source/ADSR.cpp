/*
  ==============================================================================

    ADSR.cpp
    Created: 3 Sep 2022 2:15:01am
    Author:  Joshua Cann

  ==============================================================================
*/

#include "ADSR.h"

MyEnvelope::MyEnvelope()
{
    amplitude = 0;
    hold_ = 0;
    holdCount = 0;
}

void MyEnvelope::updateSampleRate(float sampleRate)
{
    currentSampleRate = sampleRate;
}

void MyEnvelope::setADSR(float attack, float decay, float sustain, float release)
{
    attack_ = inv(attack) / currentSampleRate;
    decay_ = inv(decay) / currentSampleRate;
    sustain_ = sustain;
    release_ = inv(release) / currentSampleRate;
    amplitude = 0;
    stage = ATTACK;
    releaseTime = release;
}

void MyEnvelope::setAHDSR(float attack, float hold, float decay, float sustain, float release)
{
    setADSR(attack, decay, sustain, release);
    hold_ = hold;
}

void MyEnvelope::release() { stage = RELEASE; }

float MyEnvelope::tick()
{
    switch (stage) {
        case ATTACK:
            amplitude += attack_;
            if(amplitude >= 1) {
                amplitude = 1;
                if(hold_ != 0)
                    stage = HOLD;
                else
                    stage = DECAY;
            }
            break;
        case HOLD:
            amplitude = 1;
            holdCount += inv(hold_) / currentSampleRate;
            if(holdCount >= hold_) {
                stage = DECAY;
                holdCount = 0;
            }
            break;
        case DECAY:
            amplitude -= decay_;
            if(amplitude <= sustain_) {
                amplitude = sustain_;
                stage = SUSTAIN;
            }
            break;
        case SUSTAIN:
            amplitude = sustain_;
            break;
        case RELEASE:
            amplitude -= release_;
            if(amplitude <= 0)
                stage = OFF;
            break;
        case OFF:
               amplitude = 0;
    }
    
    return amplitude;
}

MyEnvelope::STAGE MyEnvelope::getStage()
{
    return stage;
}
