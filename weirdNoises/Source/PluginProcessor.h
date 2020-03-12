/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveTable.h"
#include "Delay.h"
class PluginController;
//==============================================================================
/**
*/
class WeirdNoisesAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    WeirdNoisesAudioProcessor();
    ~WeirdNoisesAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    double waveTableSorter();

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WeirdNoisesAudioProcessor)
    
    waveTable WaveTableSine;
    waveTable WaveTableTri;
    waveTable WaveTableSqu;
    waveTable WaveTableSaw;
    waveTable WaveTableSawInv;
    
    
    double m_cutoffA = 0.5, m_cutoffB = 0.5, m_waveTableEndValue = 0, m_amp = 0.2;
    
    double m_sineAmp = 0.2, m_triangleAmp = 0.2, m_sawAmp = 0.2, m_sawInvertedAmp = 0.2, m_squareAmp = 0.2;
    
    bool m_sineSelector = false, m_triangleSelector = false, m_sawSelector = false, m_sawInvertedSelector = false, m_squareSelector = false;
    
    friend class PluginController;
    
};
