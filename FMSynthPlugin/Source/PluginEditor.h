/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MySlider.h"
#include "OscillatorComponent.h"
#include "GlobalControls.h"
#include "EffectsRack.h"

#define NUM_SLIDERS 6

//==============================================================================
/**
*/
class FMSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FMSynthAudioProcessorEditor (FMSynthAudioProcessor&);
    ~FMSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MySlider slider[NUM_SLIDERS];
    OscillatorComponent oscPanel[4];
    GlobalControls globalControls;
    EffectsRack effectsRack;
    
    FMSynthAudioProcessor& audioProcessor;
    
    std::string labels[4] = { "Osc D - Modulator", "Osc C - Modulator", "Osc B - Modulator", "Osc A - Carier"};
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> coarseAttachment[4];
    std::unique_ptr<SliderAttachment> gainAttachment[4];
    
    std::unique_ptr<SliderAttachment> attackAttachment[4];
    std::unique_ptr<SliderAttachment> decayAttachment[4];
    std::unique_ptr<SliderAttachment> sustainAttachment[4];
    std::unique_ptr<SliderAttachment> releaseAttachment[4];
    
    std::unique_ptr<SliderAttachment> filterCutoffAttachment;
    std::unique_ptr<SliderAttachment> masterGainAttachment;
    std::unique_ptr<SliderAttachment> FMToneAttachment;
    
    std::unique_ptr<SliderAttachment> distDriveAttachment;
    std::unique_ptr<SliderAttachment> distShapeAttachment;
    std::unique_ptr<SliderAttachment> distMixAttachment;
    
    std::unique_ptr<SliderAttachment> tremRateAttachment;
    std::unique_ptr<SliderAttachment> tremDepthAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FMSynthAudioProcessorEditor)
};
