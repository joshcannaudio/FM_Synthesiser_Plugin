/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FMSynthAudioProcessorEditor::FMSynthAudioProcessorEditor (FMSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (750, 600);
    
    for(int i = 0; i < 4; i++)
        addAndMakeVisible(oscPanel[i]);
    
    addAndMakeVisible(globalControls);
    addAndMakeVisible(effectsRack);
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    // Oscillator A
    coarseAttachment[0] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter1", oscPanel[0].oscControls[0]);
    gainAttachment[0] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter2", oscPanel[0].oscControls[1]);
    
    attackAttachment[0] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter3", oscPanel[0].envelopeSlider[0]);
    decayAttachment[0] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter4", oscPanel[0].envelopeSlider[1]);
    sustainAttachment[0] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter5", oscPanel[0].envelopeSlider[2]);
    releaseAttachment[0] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter6", oscPanel[0].envelopeSlider[3]);
    
    // Oscillator B
    coarseAttachment[1] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter7", oscPanel[1].oscControls[0]);
    gainAttachment[1] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter8", oscPanel[1].oscControls[1]);
    
    attackAttachment[1] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter9", oscPanel[1].envelopeSlider[0]);
    decayAttachment[1] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter10", oscPanel[1].envelopeSlider[1]);
    sustainAttachment[1] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter11", oscPanel[1].envelopeSlider[2]);
    releaseAttachment[1] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter12", oscPanel[1].envelopeSlider[3]);
    
    // Oscillator C
    coarseAttachment[2] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter13", oscPanel[2].oscControls[0]);
    gainAttachment[2] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter14", oscPanel[2].oscControls[1]);
    
    attackAttachment[2] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter15", oscPanel[2].envelopeSlider[0]);
    decayAttachment[2] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter16", oscPanel[2].envelopeSlider[1]);
    sustainAttachment[2] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter17", oscPanel[2].envelopeSlider[2]);
    releaseAttachment[2] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter18", oscPanel[2].envelopeSlider[3]);
    
    // Oscillator D
    coarseAttachment[3] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter19", oscPanel[3].oscControls[0]);
    gainAttachment[3] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter20", oscPanel[3].oscControls[1]);
    
    attackAttachment[3] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter21", oscPanel[3].envelopeSlider[0]);
    decayAttachment[3] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter22", oscPanel[3].envelopeSlider[1]);
    sustainAttachment[3] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter23", oscPanel[3].envelopeSlider[2]);
    releaseAttachment[3] = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter24", oscPanel[3].envelopeSlider[3]);
    
    filterCutoffAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter25", globalControls.filterCutoff);
    masterGainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter26", globalControls.masterVolume);
    FMToneAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter27", globalControls.FMTone);
    
    distDriveAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter28", effectsRack.effect[0].parameters[0]);
    distShapeAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter29", effectsRack.effect[0].parameters[1]);
    distMixAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter30", effectsRack.effect[0].parameters[2]);
    
    tremRateAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter31", effectsRack.effect[1].parameters[0]);
    tremDepthAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "Parameter32", effectsRack.effect[1].parameters[1]);
    
}

FMSynthAudioProcessorEditor::~FMSynthAudioProcessorEditor()
{
    
}

//==============================================================================
void FMSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    // Oscillators
    for (int i = 0; i < 4; i++) {
        int yPos;
        i > 0 ? yPos = oscPanel[i - 1].getBottom() : yPos = 0;
        oscPanel[i].setBounds(0, yPos, getWidth() * 0.6, getHeight() * 0.25);
        oscPanel[i].setLabelText(labels[i]);
    }
    
    auto panelRight = oscPanel[0].getRight();
    
    // Global Controls
    globalControls.setBounds(panelRight, 0, getWidth() * 0.4, getHeight() * 0.25);
    
    // Effects Rack
    effectsRack.setBounds(panelRight, globalControls.getBottom(), getWidth() * 0.4, getHeight() * 0.5);
}

void FMSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
