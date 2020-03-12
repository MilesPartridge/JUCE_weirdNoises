/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
WeirdNoisesAudioProcessor::WeirdNoisesAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif

{
}

WeirdNoisesAudioProcessor::~WeirdNoisesAudioProcessor()
{
}

//==============================================================================
const String WeirdNoisesAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WeirdNoisesAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WeirdNoisesAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WeirdNoisesAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WeirdNoisesAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WeirdNoisesAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WeirdNoisesAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WeirdNoisesAudioProcessor::setCurrentProgram (int index)
{
}

const String WeirdNoisesAudioProcessor::getProgramName (int index)
{
    return {};
}

void WeirdNoisesAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void WeirdNoisesAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    WaveTableSine.setSampleRate(sampleRate);
    WaveTableTri.setSampleRate(sampleRate);
    WaveTableSqu.setSampleRate(sampleRate);
    WaveTableSaw.setSampleRate(sampleRate);
    WaveTableSawInv.setSampleRate(sampleRate);
    WaveTableSine.sine();
    WaveTableTri.triangle();
    WaveTableSqu.square();
    WaveTableSaw.saw();
    WaveTableSawInv.invertedSaw();
    
    
    
}

void WeirdNoisesAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WeirdNoisesAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void WeirdNoisesAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    float* const leftSpeaker = buffer.getWritePointer(0);
    float* const rightSpeaker = buffer.getWritePointer(1);
    int numSamples = buffer.getNumSamples();

    
    for (int sample = 0; sample < numSamples; ++sample) {
        
            leftSpeaker[sample] = waveTableSorter();
            rightSpeaker[sample] = waveTableSorter();
            
            WaveTableSine.phaseIncrement();
            WaveTableTri.phaseIncrement();
            WaveTableSqu.phaseIncrement();
            WaveTableSaw.phaseIncrement();
            WaveTableSawInv.phaseIncrement();
        }
    
    //lowpass
    /*
        leftSpeaker[0] = ((m_cutoffA * WaveTable.processor()) + (m_cutoffB * lastSampleLeft) * 0.25);
        rightSpeaker[0] = ((m_cutoffA * WaveTable.processor()) + (m_cutoffB * lastSampleRight) * 0.25);
        
        WaveTable.phaseIncrement();
    

    
    
    for (int sample = 1; sample < numSamples; ++sample) {
        
        delayed = sample - 1;
        
            leftSpeaker[sample] = ((m_cutoffA * WaveTable.processor()) + (m_cutoffB * leftSpeaker[delayed]) * 0.25);
            rightSpeaker[sample] = ((m_cutoffA * WaveTable.processor()) + (m_cutoffB * rightSpeaker[delayed]) * 0.25);
            
            WaveTable.phaseIncrement();
        

        
        
    }
    lastSampleLeft = leftSpeaker[buffer.getNumSamples()-1];
    lastSampleRight = rightSpeaker[buffer.getNumSamples()-1];

     */
     }

//==============================================================================
bool WeirdNoisesAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* WeirdNoisesAudioProcessor::createEditor()
{
    return new WeirdNoisesAudioProcessorEditor (*this);
}

//==============================================================================
void WeirdNoisesAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WeirdNoisesAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WeirdNoisesAudioProcessor();
}




double WeirdNoisesAudioProcessor::waveTableSorter(){
    
    m_waveTableEndValue = 0;
    
    if (m_sineSelector) {
        m_waveTableEndValue += WaveTableSine.processor() * m_sineAmp;
    }
    if (m_squareSelector) {
        m_waveTableEndValue += WaveTableSqu.processor() * m_squareAmp;
    }
    if (m_triangleSelector) {
        m_waveTableEndValue += WaveTableTri.processor() * m_triangleAmp;
    }
    if (m_sawSelector) {
        m_waveTableEndValue += WaveTableSaw.processor() * m_sawAmp;
    }
    if (m_sawInvertedSelector) {
        m_waveTableEndValue += WaveTableSawInv.processor() * m_sawInvertedAmp;
    }

    return m_waveTableEndValue * m_amp;
}
