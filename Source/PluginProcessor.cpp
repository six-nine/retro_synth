/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RetroSynthAudioProcessor::RetroSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParams())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

RetroSynthAudioProcessor::~RetroSynthAudioProcessor()
{
}

//==============================================================================
const juce::String RetroSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RetroSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RetroSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RetroSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double RetroSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RetroSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RetroSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RetroSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String RetroSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void RetroSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void RetroSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock){
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < synth.getNumVoices(); i++){
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))){
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void RetroSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RetroSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void RetroSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int i = 0; i < synth.getNumVoices(); i++){
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))){
            // TODO: oscillator, ADSR, LFO control
            
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");
            
            auto& fmDepth = *apvts.getRawParameterValue("FM_DEPTH");
            auto& fmFrequency = *apvts.getRawParameterValue("FM_FREQUENCY");
            
            auto& oscillatorWave = *apvts.getRawParameterValue("OSCILLATORWAVETYPE");
            
            voice->update(attack.load(), decay.load(), sustain.load(), release.load());
            voice->getOscillator().setFmParameters(fmDepth.load(), fmFrequency.load());
            voice->getOscillator().setWaveType(oscillatorWave.load());
        }
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool RetroSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* RetroSynthAudioProcessor::createEditor()
{
    return new RetroSynthAudioProcessorEditor (*this);
}

//==============================================================================
void RetroSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void RetroSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RetroSynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout RetroSynthAudioProcessor::createParams() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSCILLATOR", "Oscillator", juce::StringArray{"Sin", "Saw", "Square"}, 0));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FM_FREQUENCY", "FM Frequency", juce::NormalisableRange<float>{0.0f, 1000.0f}, 5.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FM_DEPTH", "FM Depth", juce::NormalisableRange<float>{0.0f, 1000.0f}, 100.0f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>{0.1f, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>{0.1f, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>{0.1f, 1.0f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>{0.1f, 3.0f}, 0.4f));
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSCILLATORWAVETYPE", "Oscillator wave type", juce::StringArray{"Sin", "Saw", "Square"}, 0, ""));
    return { params.begin(), params.end()  };
}
