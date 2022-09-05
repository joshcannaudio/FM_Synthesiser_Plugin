/*
  ==============================================================================

    SynthVoice.h
    Created: 9 Aug 2022 11:21:26am
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "ADSR.h"
#include "MyFMSynth.h"

class SynthVoice : public SynthesiserVoice {
public:
    
    /** Contructor, called when a new instance is created */
    SynthVoice();
    
    int getLongestReleaseIndex();
    
    /** Checks to see if the synthesiser can play sound */
    bool canPlaySound(SynthesiserSound* sound) override;
    
    /** Called when a note on message is recieved, deals with setting oscillators and envelopes which dont need to be set in the audio process */
    void startNote(int midiNoteNumber,
                    float velocity,
                    SynthesiserSound*,
                    int currentPitchWheelPosition) override;
    
    /** Called when note off midi message is recieved, used to clear the note and frees up a voice for another note unless allowTailOff is true */
    void stopNote(float velocity, bool allowTailOff) override;
    
    /** Renders the next block of audio, most of the synthesis processing is done here */
    void renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;
    
    /** Called when recieving CC message from controller */
    void controllerMoved(int controllerNumber, int newControllerValue) override;
 
    /** Called when the pitch wheel moves */
    void pitchWheelMoved(int newPitchWheelValue) override;
    
//    void getParameters(const float coarse, const float gain, const float attack, const float sustain, const float decay, const float release);
    
    void getParameters(AudioProcessorValueTreeState& valueTree);
    
    float dBtoAmplitude(float dB)
    {
        float amplitude = pow(10, dB / 20);
        if(dB <= -60)
            amplitude = 0;
        return amplitude;
    }
    
//    /** Finds longest release to enable all envelopes to finish releasing before  the current note is cleared
//        @return the index of the envelope array which has the longest release
//     */
//    int getLongestReleaseIndex();
    
private:
    MyFMSynth fmSynth;
    MyEnvelope envelope[4];
    float amplitude = 0;
    
    AudioProcessorValueTreeState* apvts;
    
    float coarse[4], filterCutoff;
    float gain[4], attack[4], decay[4], sustain[4], release[4];
    float masterGain, FMTone;
};
