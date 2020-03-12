/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PluginController.h"
#include "LookAndFeelMiles.h"

//==============================================================================
/**
*/
class WeirdNoisesAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    WeirdNoisesAudioProcessorEditor (WeirdNoisesAudioProcessor&);
    ~WeirdNoisesAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WeirdNoisesAudioProcessor& processor;
    
    LookAndFeelMiles m_lookAndFeelMiles;
    
    TextButton m_buttonTriangle, m_buttonSquare, m_buttonSine, m_buttonSaw, m_buttonInvertedSaw;
    TextButton m_Scratch, m_Itch, m_Garble, m_Gobble;
    Slider m_PWM_Slider, m_cutoffSlider, m_sineAmountSlider, m_sawAmountSlider, m_sawInvAmountSlider, m_triAmountSlider, m_squAmountSlider;
    Slider m_sineFreqSlider, m_sawFreqSlider, m_sawInvFreqSlider, m_triFreqSlider, m_squFreqSlider;
    
    waveTable wave_table;
    
    PluginController m_controller;
    
    friend class PluginController;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WeirdNoisesAudioProcessorEditor)
};
