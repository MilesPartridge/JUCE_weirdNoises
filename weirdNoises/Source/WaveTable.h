/*
  ==============================================================================

    WaveTable.h
    Created: 7 Mar 2019 9:41:03am
    Author:  Miles Partridge

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
class PluginController;

class waveTable
{
public:
    waveTable(double sampleRate = 44100);
    double processor();
    double phaseIncrement();
    void setSampleRate(double sampleRate = 44100);
    double getSize();
    void setPWM(double pwmValue = 2);
    void setFreq(double frequency = 190);
    double getFreq();
    void triangle();
    void sine();
    void square();
    void saw();
    void invertedSaw();
    
private:
    Array<float> m_waveTable;
    double m_wtSize, m_frequency, m_phase, m_increment, m_amplitude, m_PWM, m_sampleRate, m_processed, m_wtSizeGuarded, m_waveTablePoint;
    bool m_squareWaveInUse;
    
    friend class PluginController;
};
