/*
  ==============================================================================

    Delay.cpp
    Created: 12 Mar 2019 5:06:17pm
    Author:  Miles Partridge

  ==============================================================================
*/

#include "Delay.h"

///Basic Delay Unit constructor with a default size of 128 samples
DelayUnit::DelayUnit(int maximumDelay) :
    m_buffer(maximumDelay), //Initialises values in the order of declaration
    m_writePos(0),
    m_maxDelay(maximumDelay)
{
    std::cout<<"Delay Unit Constructed with max size of: "<<m_maxDelay<<std::endl;
};

///Advance the write position and check that it is in bounds
void DelayUnit::tick()
{
    ++m_writePos;
    
    while (m_writePos > m_maxDelay) m_writePos -= m_maxDelay;
    while (m_writePos < 0) m_writePos += m_maxDelay;
}

///Returns a delayed signal/value at a given Sample Time. 
float DelayUnit::getDelay(float delayTime)
{
    
    double remainder, prevIndex, nextIndex;
    
    remainder = modf((m_writePos - delayTime), &prevIndex);
    nextIndex = prevIndex + 1;
    
    while (prevIndex > m_maxDelay) prevIndex -= m_maxDelay;
    while (prevIndex < 0) prevIndex += m_maxDelay;
    
    while (nextIndex > m_maxDelay) nextIndex -= m_maxDelay;
    while (nextIndex < 0) nextIndex += m_maxDelay;
    
    float previous = m_buffer[(int)prevIndex];
    float next = m_buffer[(int)nextIndex];
    
    
    return(previous*(1-remainder)+next*remainder);
    
}

///Writes sample to buffer. Clips audio to range -1 to 1.
void DelayUnit::writeDelay(float sample, bool clip, bool replace)
{
    if (clip) //Allows clipping functionality to be turned off
    {
        if (sample > 1) sample = 1;
        if (sample < -1) sample = -1;
    }
    if (replace)
    {
        m_buffer[m_writePos] = sample;
    }
    else
    {
        m_buffer[m_writePos] += sample;
        
        if (clip) //Allows clipping functionality to be turned off
        {
            if (m_buffer[m_writePos] > 1) m_buffer[m_writePos] = 1;
            if (m_buffer[m_writePos] < -1) m_buffer[m_writePos] = -1;
        }
    }
}

///Clears the buffer when delay is resumed after a pause.
void DelayUnit::clear()
{
    m_buffer.clear();
}
