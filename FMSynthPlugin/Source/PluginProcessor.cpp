/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FMSynthAudioProcessor::FMSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
    for(int i = 0; i < 8; i++)
        synthesiser.addVoice(new SynthVoice());
    synthesiser.addSound(new SynthSound());
}

FMSynthAudioProcessor::~FMSynthAudioProcessor()
{
}

//==============================================================================
const juce::String FMSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FMSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FMSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FMSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FMSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FMSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FMSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FMSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FMSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void FMSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FMSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synthesiser.setCurrentPlaybackSampleRate(sampleRate);
    processor.prepareToPlay(sampleRate);
}

void FMSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FMSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FMSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for( int i = 0; i < synthesiser.getNumVoices(); ++i) {
        if(auto voice = dynamic_cast<SynthVoice*>(synthesiser.getVoice(i)))
        {
//            auto& coarseA = *apvts.getRawParameterValue("Parameter1");
//            auto& gainA = *apvts.getRawParameterValue("Parameter2");
//
//            auto& attackA = *apvts.getRawParameterValue("Parameter3");
//            auto& decayA = *apvts.getRawParameterValue("Parameter4");
//            auto& sustainA = *apvts.getRawParameterValue("Parameter5");
//            auto& releaseA = *apvts.getRawParameterValue("Parameter6");
//
//            voice->getParameters(coarseA.load(), gainA.load(), attackA.load(), decayA.load(), sustainA.load(), releaseA.load());
            voice->getParameters(apvts);
        }
    }
    
    
    synthesiser.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    processor.process(buffer.getReadPointer(0),
                      buffer.getReadPointer(1),
                      buffer.getWritePointer(0),
                      buffer.getWritePointer(1),
                      buffer.getNumSamples(),
                      apvts);
}

//==============================================================================
bool FMSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FMSynthAudioProcessor::createEditor()
{
    return new FMSynthAudioProcessorEditor (*this);
}

//==============================================================================
void FMSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FMSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FMSynthAudioProcessor();
}

AudioProcessorValueTreeState::ParameterLayout FMSynthAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    // Oscillator D
    params.push_back (std::make_unique<AudioParameterInt>(ParameterID { "Parameter1", 1 }, "Coarse A", -12, 24, 0));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter2", 2 }, "Volume A", -60.f, 0.f, -60.f));
    
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter3", 3 }, "Attack A", 0.f, 2.f, 0.05f));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter4", 4 }, "Decay A", 0.f, 2.f, 0.2f));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter5", 5 }, "Sustain A", -60.f, 0.f, -6.f));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter6", 6 }, "Release A", 0.f, 2.f, 0.2f));
    
    // Oscillator C
    params.push_back (std::make_unique<AudioParameterInt>(ParameterID { "Parameter7", 7 }, "Coarse B", -12, 24, 0));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter8", 8 }, "Volume B", -60.f, 0.f, -60.f));
    
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter9", 3 }, "Attack B", 0.f, 2.f, 0.05f));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter10", 4 }, "Decay B", 0.f, 2.f, 0.2f));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter11", 5 }, "Sustain B", -60.f, 0.f, -6.f));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter12", 6 }, "Release B", 0.f, 2.f, 0.2f));
    
    // Oscillator B
    params.push_back (std::make_unique<AudioParameterInt>(ParameterID { "Parameter13", 1 }, "Coarse C", -12, 24, 0));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter14", 2 }, "Volume C", -60.f, 0.f, -60.f));
    
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter15", 3 }, "Attack C", 0.f, 2.f, 0.05f));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter16", 4 }, "Decay C", 0.f, 2.f, 0.2f));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter17", 5 }, "Sustain C", -60.f, 0.f, -6.f));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter18", 6 }, "Release C", 0.f, 2.f, 0.2f));
    
    // Oscillator A
    params.push_back (std::make_unique<AudioParameterInt>(ParameterID { "Parameter19", 1 }, "Coarse D", -12, 24, 0));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter20", 2 }, "Volume D", -60.f, 0.f, -6.f));
    
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter21", 3 }, "Attack D", 0.f, 2.f, 0.05f));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter22", 4 }, "Decay D", 0.f, 2.f, 0.2f));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter23", 5 }, "Sustain D", -60.f, 0.f, -6.f));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter24", 6 }, "Release D", 0.f, 2.f, 0.2f));
    
    // Global Parameters
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter25", 6 }, "Filter Cutoff", 20, 20000, 8000));
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter26", 6 }, "Master Gain", -60.f, 0.f, -6.f));
    params.push_back (std::make_unique<AudioParameterInt>(ParameterID { "Parameter27", 6 }, "FM Tone", 0, 100, 30));
    
    // Effects
    params.push_back (std::make_unique<AudioParameterInt>(ParameterID { "Parameter28", 6 }, "Dist Drive", 0, 100, 20));
    params.push_back (std::make_unique<AudioParameterInt>(ParameterID { "Parameter29", 6 }, "Dist Shape", 0, 100, 80));
    params.push_back (std::make_unique<AudioParameterInt>(ParameterID { "Parameter30", 6 }, "Dist Mix", 0, 100, 0));
    
    params.push_back (std::make_unique<AudioParameterFloat>(ParameterID { "Parameter31", 6 }, "Trem Rate", 0, 20, 5));
    params.push_back (std::make_unique<AudioParameterInt>(ParameterID { "Parameter32", 6 }, "Trem Depth", 0, 100, 0));
    
    return { params.begin(), params.end() };
}
