/*
  ==============================================================================

    PluginController.h
    Created: 7 Mar 2019 11:11:10am
    Author:  Miles Partridge

  ==============================================================================
*/

#pragma once
class WeirdNoisesAudioProcessor;
class WeirdNoisesAudioProcessorEditor;
class waveTable;


class PluginController 
{
public:
    PluginController(WeirdNoisesAudioProcessorEditor* editor, WeirdNoisesAudioProcessor* processor);
    
    ~PluginController();
    
    void ScratchFrequencyDown();
    void ScratchFrequencyUp();
    void AmpLevelDown();
    void AmpLevelUp();
    
private:
    WeirdNoisesAudioProcessorEditor* m_editor;
    WeirdNoisesAudioProcessor* m_processor;
    double triFreq = 0, sawFreq = 0, sawInvFreq = 0, squFreq = 0, sineFreq = 0;
    double triPreviousFreq = 0, sawPreviousFreq = 0, sawInvPreviousFreq = 0, squPreviousFreq = 0, sinePreviousFreq = 0;
    double triPreviousAmp = 0, sawPreviousAmp = 0, sawInvPreviousAmp = 0, squPreviousAmp = 0, sinePreviousAmp = 0;
    double triPreviousAmpCopy = 0, sawPreviousAmpCopy = 0, sawInvPreviousAmpCopy = 0, squPreviousAmpCopy = 0, sinePreviousAmpCopy = 0;
    int randomNumber = 0, forLoopRandomizer = 1, forLoopRandomizerNested = 1, m_switcher = 1;
    bool triangleState, sawState, sawInvState, squState, sineState;
};
