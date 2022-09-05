/*
  ==============================================================================

    Effects.cpp
    Created: 4 Sep 2022 10:41:29pm
    Author:  Joshua Cann

  ==============================================================================
*/

#include "Effects.h"

void MyFilter::setCutoff(float coeff)
{
    a = coeff;
    b = 1 - a;
}

float MyFilter::getCutoff()
{
    float frequency = acos(1 - ((a * a) / (2 * b))) * (currentSampleRate / (2 * M_PI));
    std::cout << frequency << std::endl;
    return frequency;
//        14145.62
}

float MyFilter::tick(float input)
{
    currentSample = input * a;
    currentSample += (previousSample * b);
    previousSample = currentSample;
    return currentSample;
}

float Distortion::getSoftClip(float input, float inGain, float aCoeff)
{
    aCoeff = aCoeff * 9998.9 + 1.1;
    inGain = inGain * 4 + 1;
    input *= inGain;
    if(input > 1)
       input = 1;
    else if(input < -1)
        input = -1;
    
    float shapedWave = aCoeff / (aCoeff - 1.0);
    
    if(input > 0)
       shapedWave *= (1.0 - pow(aCoeff, -input));
    else
       shapedWave *= (-1.0 + pow(aCoeff, input));
    
    return shapedWave;
}

void MyModulation::setLFO(float rate, float depth)
{
    fDepth = depth * 0.5;
    sine.setFrequency(rate);
}

float MyModulation::tick()
{
    return (sine.nextSample() * fDepth + 0.5) * 2;
}
