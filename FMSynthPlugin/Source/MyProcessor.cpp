/*
  ==============================================================================

    MyProcessor.cpp
    Created: 9 Aug 2022 11:24:53am
    Author:  Joshua Cann

  ==============================================================================
*/

#include "MyProcessor.h"

MyProcessor::MyProcessor()
{
    
}

MyProcessor::~MyProcessor()
{
    
}

void MyProcessor::prepareToPlay(float currentSampleRate)
{
    
}

void MyProcessor::process(const float *pfInBuffer0, const float *pfInBuffer1, float *pfOutBuffer0, float *pfOutBuffer1, int numSamples, AudioProcessorValueTreeState& apvts)
{
    float fIn0, fIn1, fOut0 = 0, fOut1 = 0;
    
    float distDrive = apvts.getRawParameterValue("Parameter28")->load() * 0.01;
    float distShape = apvts.getRawParameterValue("Parameter29")->load() * 0.01;
    float distMix = apvts.getRawParameterValue("Parameter30")->load() * 0.01;
    
    float tremRate = apvts.getRawParameterValue("Parameter31")->load();
    float tremDepth = apvts.getRawParameterValue("Parameter32")->load() * 0.01;
    
    tremelo.setLFO(tremRate, tremDepth);
    
    for(int sample = 0; sample < numSamples; ++sample)
    {
        fIn0 = pfInBuffer0[sample];
        fIn1 = pfInBuffer1[sample];

        float wet = distortion.getSoftClip((fIn0 + fIn1) * 0.5, distDrive, distShape);
        fIn0 = ((wet * distMix) + (fIn0 * (1 - distMix)));
        fIn1 = ((wet * distMix) + (fIn1 * (1 - distMix)));

        float trem = tremelo.tick();
        fIn0 *= trem;
        fIn1 *= trem;
        
        fOut0 = fIn0;
        fOut1 = fIn1;
        
        ++pfOutBuffer0[sample] = fOut0;
        ++pfOutBuffer1[sample] = fOut1;
    }
    
}
