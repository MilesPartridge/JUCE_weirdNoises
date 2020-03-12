/*
  ==============================================================================

    Delay.h
    Created: 12 Mar 2019 4:47:41pm
    Author:  Miles Partridge

  ==============================================================================
*/

#pragma once
#include <iostream>
#include <vector>
#include <math.h>

typedef std::vector<float> DelayBuffer;

class DelayUnit
{
public:
    ///Basic Delay Unit constructor with a default size of 128 samples
    DelayUnit(int maximumDelay = 128);
    
    ///Advance the write position and check that it is in bounds
    void tick();
    
    ///Returns a delayed signal/value at a given Sample Time. No interpolation is used
    float getDelay(float delayTime);
    
    ///Writes sample to buffer. Clips audio to range -1 to 1.
    void writeDelay(float sample, bool clip = true, bool replace = true);
    
    ///Clears the buffer when delay is resumed after a pause.
    void clear();
    
private:
    
    DelayBuffer m_buffer;
    int m_writePos, m_maxDelay;
    
};
