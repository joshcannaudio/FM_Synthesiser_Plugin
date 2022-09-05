/*
  ==============================================================================

    SineOscillator.cpp
    Created: 3 Sep 2022 1:49:34am
    Author:  Joshua Cann

  ==============================================================================
*/

#include "SineOscillator.h"

SineOscillator::SineOscillator()
{
}

SineOscillator::~SineOscillator()
{
    
}

float SineOscillator::nextSample()
{
    float nextSample = renderWaveShape(phasePosition);
    
    phasePosition += phaseIncrement;
    if(phasePosition > MathConstants<float>::twoPi)
        phasePosition -= MathConstants<float>::twoPi;
    
    return nextSample;
}

void SineOscillator::setFrequency(float freq)
{
    frequency = freq;
    updatePhaseIncrement();
}

const float SineOscillator::getFrequency()
{
    return frequency;
}

void SineOscillator::updateSampleRate(float sampleRate)
{
    currentSampleRate = sampleRate;
    updatePhaseIncrement();
}

float SineOscillator::renderWaveShape(float phase)
{
    return std::sin(phase);
}

void SineOscillator::updatePhaseIncrement()
{
    phaseIncrement = (MathConstants<float>::twoPi * frequency) / currentSampleRate;
}


