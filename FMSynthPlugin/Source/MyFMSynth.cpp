/*
  ==============================================================================

    MyFMSynth.cpp
    Created: 3 Sep 2022 10:21:03am
    Author:  Joshua Cann

  ==============================================================================
*/

#include "MyFMSynth.h"

MyFMSynth::MyFMSynth()
{
   for(int i = 0; i < 3; i++) {
       fModulator[i] = 0;
   }
   fCarrier = 0;
   fFrequency = 0;
}

MyFMSynth::~MyFMSynth() {}

void MyFMSynth::updateSampleRate(float sampleRate)
{
    modulator[0].updateSampleRate(sampleRate);
    modulator[1].updateSampleRate(sampleRate);
    modulator[2].updateSampleRate(sampleRate);
    carrier.updateSampleRate(sampleRate);
}

float MyFMSynth::getCoarseTune(float frequency, float coarse) // +- 1 for +- Octave
{
   coarse /= 12;
   float tune = powf(2.0, coarse);
   return frequency * tune;
}

void MyFMSynth::setFrequency(float freq)
{
    fFrequency = freq;
}

// D->C->B->A ===========================================================================================
void MyFMSynth::setFM(float fIndex, float fOscGain[4], float fEnv[4], float fOscTune[4]) //setFM with 4 operators
{
   modulator[0].setModulator(fIndex, getCoarseTune(fFrequency, fOscTune[0]));
   fModulator[0] = modulator[0].tickModulator() * fOscGain[0];
   fModulator[0] *= fEnv[0];

   modulator[1].setModulator(fIndex, getCoarseTune(fFrequency, fOscTune[1]) + fModulator[0]);
   fModulator[1] = modulator[1].tickModulator() * fOscGain[1];
   fModulator[1] *= fEnv[1];

   modulator[2].setModulator(fIndex, getCoarseTune(fFrequency, fOscTune[2]) + fModulator[1]);
   fModulator[2] = modulator[2].tickModulator() * fOscGain[2];
   fModulator[2] *= fEnv[2];

   carrier.setOscillator(getCoarseTune(fFrequency, fOscTune[3]) + fModulator[2]);
   fCarrier = carrier.tickCarrier() * fOscGain[3];
   fCarrier *= fEnv[3];

   fOut = fCarrier;
}

float MyFMSynth::nextSample()
{
   return fOut;
}
