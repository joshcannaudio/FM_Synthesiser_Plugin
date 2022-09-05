/*
  ==============================================================================

    SynthSound.h
    Created: 9 Aug 2022 11:21:40am
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {
public:
    /** Returns true to say note should be played */
    bool appliesToNote(int midiNoteNumber) override { return true; }
    
    /** Returns true to say it applies to channel */
    bool appliesToChannel(int midiChannel) override { return true; }
};
