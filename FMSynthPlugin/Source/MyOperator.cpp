/*
  ==============================================================================

    MyOperator.cpp
    Created: 3 Sep 2022 10:21:11am
    Author:  Joshua Cann

  ==============================================================================
*/

#include "MyOperator.h"

MyOperator::MyOperator()
{
}

void MyOperator::reset()
{
//    carrier.reset();
//    modulator.reset();
}

void MyOperator::updateSampleRate(float sampleRate)
{
    modulator.updateSampleRate(sampleRate);
    carrier.updateSampleRate(sampleRate);
}

void MyOperator::setOscillator(float fFrequency)
{
    carrier.setFrequency(blit(fFrequency));
}

void MyOperator::setModulator(float fIndex, float fFrequency)
{
    fc = fFrequency;
    fd = fc;
    I = fIndex;
    Ifd = fd * I;
    modulator.setFrequency(blit(fd));
}

float MyOperator::tickCarrier()
{
    return carrier.nextSample();
}

float MyOperator::tickModulator()
{
    return modulator.nextSample() * Ifd;
}

float MyOperator::blit(float frequency)
{
    auto nyquist = currentSampleRate * 0.5;
    if(frequency > nyquist)
        frequency = nyquist;
    return frequency;
}
