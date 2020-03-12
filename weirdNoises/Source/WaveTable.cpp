/*
  ==============================================================================

    WaveTable.cpp
    Created: 7 Mar 2019 9:41:03am
    Author:  Miles Partridge

  ==============================================================================
*/

#include "WaveTable.h"


waveTable::waveTable(double sampleRate): m_sampleRate(sampleRate)
{
    m_frequency = 190;
    m_phase = 0;
    m_wtSize = 1024;
    m_wtSizeGuarded = m_wtSize + 1;
    m_PWM = 2;
    m_increment = m_frequency / m_sampleRate;
    m_amplitude = 0.25;
}

void waveTable::setSampleRate(double sampleRate){
    m_sampleRate = sampleRate;
    m_increment = m_frequency / m_sampleRate;
}

double waveTable::getSize(){
    return m_wtSize;
}

void waveTable::setPWM(double pwmValue){
    m_PWM = pwmValue;
}

void waveTable::setFreq(double frequency){
    m_frequency = frequency;
}

double waveTable::getFreq(){
    return m_frequency;
}

double waveTable::processor(){
    if (m_squareWaveInUse) {
    // work out which sample to point at in the table, then make a pulse wave using m_PWM
    m_waveTablePoint = m_phase * m_wtSize;
    
    while (m_waveTablePoint >= m_wtSize) {
        m_waveTablePoint -= m_wtSize;
    }
    while (m_waveTablePoint < 0) {
        m_waveTablePoint += m_wtSize;
    }
    
        if (m_waveTablePoint < m_PWM){
            m_processed = 1;
        }
        else{
            m_processed = -1;
        }
        
    return m_processed;                         
    }
    else    {
        // work out which sample to point at in the table, and keep it in the range of the table
        m_waveTablePoint = m_phase * m_wtSize;
        
        while (m_waveTablePoint >= m_wtSize) {
            m_waveTablePoint -= m_wtSize;
        }
        while (m_waveTablePoint < 0) {
            m_waveTablePoint += m_wtSize;
        }
        
        // m_waveTablePoint will probably be in between 2 indexes of the table, so interpolate between them here
        int base, next;                     //ideas from The Audio Programming Book
        double fraction, val, slope;
        base = (int)m_waveTablePoint;
        next = base + 1;                        //this will not go out of bounds thanks to the Guard Point
        
        fraction = m_waveTablePoint - base;
        val = m_waveTable[base];
        slope = m_waveTable[next] - val;
        val += (fraction * slope);
        
        
        
        m_processed = val;                   // need * m_amplitude
        return m_processed;
    }
}

double waveTable::phaseIncrement(){
    m_phase += m_increment;
        
    while (m_phase >= 1){
        m_phase -= 1;
    }
        
        return m_phase;
}

////// need to set guard point and m_squareWaveInUse for each waveform

void waveTable::triangle(){
    int i;
    for (i = 0; i<m_wtSize; ++i) {
        if (i < (m_wtSize / 4)) {
            m_waveTable.insert(i, (1 / m_wtSize) * i * 4);              //starts 0,. goes to 1 in the 1st quarter of the wavetable
        }
        else if (i < ((m_wtSize / 4) * 3)) {
            m_waveTable.insert(i, (1 / m_wtSize) * ((m_wtSize / 2) - i) * 4);       //then goes to -1 by 3/4s wavetable
        }
        else {
            m_waveTable.insert(i, (1 / m_wtSize) * (i - m_wtSize) * 4);     //then goes back to 0 in the final q
        }
    }
    ++i;
    m_waveTable.insert(i, m_waveTable[0]);
    m_squareWaveInUse = false;
}

void waveTable::sine(){
    int i;
    for (i = 0; i<m_wtSize; ++i) {
        m_waveTable.insert(i, sin((2*double_Pi*i)/m_wtSize));
    }
    ++i;
    m_waveTable.insert(i, m_waveTable[0]);
    m_squareWaveInUse = false;
}

void waveTable::square(){
    int i;
    for (i = 0; i<m_wtSize; ++i) {
        if (i<(m_wtSize/m_PWM)) {
            m_waveTable.insert(i, 1);
        }
        else {
            m_waveTable.insert(i, -1);
        }
    }
    ++i;
    m_waveTable.insert(i, m_waveTable[0]);
    m_squareWaveInUse = true;
}

void waveTable::saw(){
    int i;
    for (i = 0; i<m_wtSize; ++i) {
        if (i<(m_wtSize/2)){
        m_waveTable.insert(i, ((1 / m_wtSize) * i) * 2);            //starts at 0, goes to 1 at halfway wtSize
        }
        else    {
        m_waveTable.insert(i, ((1 / m_wtSize) * i) * 2 - 2);    //drops to -1,  ends wavetable size at 0
            }
    }
    ++i;
    m_waveTable.insert(i, m_waveTable[0]);
    m_squareWaveInUse = false;
}

void waveTable::invertedSaw(){
    int i;
    for (i = 0; i<m_wtSize; ++i) {
        if (i<(m_wtSize/2)){
            m_waveTable.insert(i, ((1 / m_wtSize) * (m_wtSize - i)) * 2 - 2);            //starts at 0, ends at 0
        }
        else    {
            m_waveTable.insert(i, ((1 / m_wtSize) * (m_wtSize - i)) * 2);
        }
    }
    ++i;
    m_waveTable.insert(i, m_waveTable[0]);
    m_squareWaveInUse = false;
}

