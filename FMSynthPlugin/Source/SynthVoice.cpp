/*
  ==============================================================================

    SynthVoice.cpp
    Created: 9 Aug 2022 11:21:26am
    Author:  Joshua Cann

  ==============================================================================
*/

#include "SynthVoice.h"

SynthVoice::SynthVoice()
{
    for(int i = 0; i < 4; i++)
        envelope[i].updateSampleRate(getSampleRate());
    
    fmSynth.updateSampleRate(getSampleRate());
}

int SynthVoice::getLongestReleaseIndex()
{
    int releaseIndex = 0;
    float longestRelease = 0;
    for (int i = 0; i < 4; i++) {
        if(release[i] > longestRelease) {
            longestRelease = release[i];
            releaseIndex = i;
        }
    }
    return releaseIndex;
}

bool SynthVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber,
                           float velocity,
                           SynthesiserSound*,
                           int currentPitchWheelPosition)
{
//    envelope.setADSR(0.05, 0.5, 0.4, 0.3);
    
    for(int i = 0; i < 4; i++)
        envelope[i].setADSR(attack[i], decay[i], sustain[i], release[i]);
    
    fmSynth.setFrequency(MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    amplitude = velocity;
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    for(int i = 0; i < 4; i++)
        envelope[i].release();
    allowTailOff = true;
}

void SynthVoice::renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{

    
    while(--numSamples >= 0)
    {
        float oscGain[4] = { gain[0], gain[1], gain[2], gain[3] };
        float env[4];
        float oscTune[4] = { coarse[0], coarse[1], coarse[2], coarse[3] };
        
        for(int i = 0; i < 4; i++)
            env[i] = envelope[i].tick();
        
        fmSynth.setFM(FMTone, oscGain, env, oscTune);
        float sample = fmSynth.nextSample() * amplitude;
        sample *= masterGain;
        
        for(int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
        {
            outputBuffer.addSample(channel, startSample, sample);
        }
        
        if(envelope[getLongestReleaseIndex()].getStage() == MyEnvelope::STAGE::OFF)
            clearCurrentNote();
        
        ++startSample;
    }
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue){}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue){}

//void SynthVoice::getParameters(const float coarse, const float gain, const float attack, const float sustain, const float decay, const float release)
//{
//    coarse_[0] = coarse;
//    gain_[0] = gain;
//    attack_[0] = attack;
//    decay_[0] = decay;
//    sustain_[0] = sustain;
//    release_[0] = release;
//}

void SynthVoice::getParameters(AudioProcessorValueTreeState& valueTree)
{
//    apvts = &valueTree;
    coarse[0] = valueTree.getRawParameterValue("Parameter1")->load();
    gain[0] = dBtoAmplitude(valueTree.getRawParameterValue("Parameter2")->load());
    
    attack[0] = valueTree.getRawParameterValue("Parameter3")->load();
    decay[0] = valueTree.getRawParameterValue("Parameter4")->load();
    sustain[0] = dBtoAmplitude(valueTree.getRawParameterValue("Parameter5")->load());
    release[0] = valueTree.getRawParameterValue("Parameter6")->load();
    
    coarse[1] = valueTree.getRawParameterValue("Parameter7")->load();
    gain[1] = dBtoAmplitude(valueTree.getRawParameterValue("Parameter8")->load());
    
    attack[1] = valueTree.getRawParameterValue("Parameter9")->load();
    decay[1] = valueTree.getRawParameterValue("Parameter10")->load();
    sustain[1] = dBtoAmplitude(valueTree.getRawParameterValue("Parameter11")->load());
    release[1] = valueTree.getRawParameterValue("Parameter12")->load();
    
    coarse[2] = valueTree.getRawParameterValue("Parameter13")->load();
    gain[2] = dBtoAmplitude(valueTree.getRawParameterValue("Parameter14")->load());
    
    attack[2] = valueTree.getRawParameterValue("Parameter15")->load();
    decay[2] = valueTree.getRawParameterValue("Parameter16")->load();
    sustain[2] = dBtoAmplitude(valueTree.getRawParameterValue("Parameter17")->load());
    release[2] = valueTree.getRawParameterValue("Parameter18")->load();
    
    coarse[3] = valueTree.getRawParameterValue("Parameter19")->load();
    gain[3] = dBtoAmplitude(valueTree.getRawParameterValue("Parameter20")->load());
    
    attack[3] = valueTree.getRawParameterValue("Parameter21")->load();
    decay[3] = valueTree.getRawParameterValue("Parameter22")->load();
    sustain[3] = dBtoAmplitude(valueTree.getRawParameterValue("Parameter23")->load());
    release[3] = valueTree.getRawParameterValue("Parameter24")->load();
    
    filterCutoff = valueTree.getRawParameterValue("Parameter25")->load();
    masterGain = dBtoAmplitude(valueTree.getRawParameterValue("Parameter26")->load());
    FMTone = valueTree.getRawParameterValue("Parameter27")->load() * 0.3;
}
