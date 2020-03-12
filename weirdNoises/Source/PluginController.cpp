/*
  ==============================================================================

    PluginController.cpp
    Created: 7 Mar 2019 11:11:10am
    Author:  Miles Partridge

  ==============================================================================
*/

#include "PluginController.h"
#include "PluginEditor.h"
#include "PluginProcessor.h"
#include <iostream>
#include <random>

PluginController::PluginController(WeirdNoisesAudioProcessorEditor* editor, WeirdNoisesAudioProcessor* processor):
m_editor(editor),
m_processor(processor)
{
    ///////             sliders
    m_editor->m_PWM_Slider.onValueChange = [this]
    {
        m_processor->WaveTableSqu.setPWM(m_editor->m_PWM_Slider.getValue());
    };
    
    m_editor->m_cutoffSlider.onValueChange = [this]
    {
        m_processor->m_cutoffA = m_editor->m_cutoffSlider.getValue();
        m_processor->m_cutoffB = 1 - m_editor->m_cutoffSlider.getValue();
    };
    
    
    
    
    
    ///////         buttons and corresponding sliders
    m_editor->m_buttonTriangle.onClick = [this]
    {
        if(!m_processor->m_triangleSelector)
        m_processor->m_triangleSelector = true;
        else
        m_processor->m_triangleSelector = false;
            
    };
    m_editor->m_triAmountSlider.onValueChange = [this]
    {
        m_processor->m_triangleAmp = m_editor->m_triAmountSlider.getValue();
    };
    m_editor->m_triFreqSlider.onValueChange = [this]
    {
        m_processor->WaveTableTri.setFreq(m_editor->m_triFreqSlider.getValue());
        m_processor->WaveTableTri.setSampleRate(m_processor->getSampleRate());
    };
    
    
    
    m_editor->m_buttonSaw.onClick = [this]
    {
        if(!m_processor->m_sawSelector)
        m_processor->m_sawSelector = true;
        else
        m_processor->m_sawSelector = false;
    };
    m_editor->m_sawAmountSlider.onValueChange = [this]
    {
        m_processor->m_sawAmp = m_editor->m_sawAmountSlider.getValue();
    };
    m_editor->m_sawFreqSlider.onValueChange = [this]
    {
        m_processor->WaveTableSaw.setFreq(m_editor->m_sawFreqSlider.getValue());
        m_processor->WaveTableSaw.setSampleRate(m_processor->getSampleRate());
    };
    
    
    
    m_editor->m_buttonInvertedSaw.onClick = [this]
    {
        if(!m_processor->m_sawInvertedSelector)
        m_processor->m_sawInvertedSelector = true;
        else
        m_processor->m_sawInvertedSelector = false;
    };
    m_editor->m_sawInvAmountSlider.onValueChange = [this]
    {
        m_processor->m_sawInvertedAmp = m_editor->m_sawInvAmountSlider.getValue();
    };
    m_editor->m_sawInvFreqSlider.onValueChange = [this]
    {
        m_processor->WaveTableSawInv.setFreq(m_editor->m_sawInvFreqSlider.getValue());
        m_processor->WaveTableSawInv.setSampleRate(m_processor->getSampleRate());
    };
    
    
    
    m_editor->m_buttonSine.onClick = [this]
    {
        if(!m_processor->m_sineSelector)
        m_processor->m_sineSelector = true;
        else
        m_processor->m_sineSelector = false;
    };
    m_editor->m_sineAmountSlider.onValueChange = [this]
    {
        m_processor->m_sineAmp = m_editor->m_sineAmountSlider.getValue();
    };
    m_editor->m_sineFreqSlider.onValueChange = [this]
    {
        m_processor->WaveTableSine.setFreq(m_editor->m_sineFreqSlider.getValue());
        m_processor->WaveTableSine.setSampleRate(m_processor->getSampleRate());
    };
    
    
    
    m_editor->m_buttonSquare.onClick = [this]
    {
        if(!m_processor->m_squareSelector)
        m_processor->m_squareSelector = true;
        else
        m_processor->m_squareSelector = false;
    };
    m_editor->m_squAmountSlider.onValueChange = [this]
    {
        m_processor->m_squareAmp = m_editor->m_squAmountSlider.getValue();
    };
    m_editor->m_squFreqSlider.onValueChange = [this]
    {
        m_processor->WaveTableSqu.setFreq(m_editor->m_squFreqSlider.getValue());
        m_processor->WaveTableSqu.setSampleRate(m_processor->getSampleRate());
    };
    
    
    
    
    
    
    ///////         Weird Noises buttons
    //              scratch button
    m_editor->m_Scratch.onClick = [this]
    {
        triPreviousFreq = m_processor->WaveTableTri.getFreq();
        sawPreviousFreq = m_processor->WaveTableSaw.getFreq();
        sawInvPreviousFreq = m_processor->WaveTableSawInv.getFreq();
        sinePreviousFreq = m_processor->WaveTableSine.getFreq();
        squPreviousFreq = m_processor->WaveTableSqu.getFreq();
        
        triPreviousAmp = m_processor->m_triangleAmp;
        sawPreviousAmp = m_processor->m_sawAmp;
        sawInvPreviousAmp = m_processor->m_sawInvertedAmp;
        sinePreviousAmp = m_processor->m_sineAmp;
        squPreviousAmp = m_processor->m_squareAmp;
        
        std::random_device RD;
        std::mt19937 marsenneTwister(RD());
        /////     stick all this in a randomised for loop  for i = random variable then switch case random number selecting which one, then a bit of code that does a fast cut, slow up fast down, and fast up slow down
        forLoopRandomizer = marsenneTwister() % 5 + 1;
        
        for (int i = 0; i < forLoopRandomizer; i++) {
        randomNumber = marsenneTwister() % 4 + 1;
            switch (randomNumber) {
                case 1:
                    randomNumber = marsenneTwister() % 20 + 1;
                    ScratchFrequencyDown();
                    AmpLevelDown();
                    randomNumber = marsenneTwister() % 50 + 40;
                    Thread::sleep(randomNumber);
                    // make the above freq and amp downs and ups into functions, then call them random amounts of times, if they are called faster then call them more often.
                    //when the frequency is lower, the time it delays needs to be longer. This could be done with if statements, if below threshold then add random number % this amount
                    AmpLevelUp();
                    randomNumber = marsenneTwister() % 5 + 1;
                    ScratchFrequencyUp();
                    break;
                    
                case 2:
                    //////// 2nd down and up
                    randomNumber = marsenneTwister() % 50 + 20;
                    Thread::sleep(randomNumber);
                    randomNumber = marsenneTwister() % 30 + 3;
                    ScratchFrequencyDown();
                    AmpLevelDown();
                    randomNumber = marsenneTwister() % 90 + 40;
                    Thread::sleep(randomNumber);
                    AmpLevelUp();
                    randomNumber = marsenneTwister() % 20 + 1;
                    ScratchFrequencyUp();
                    break;
                    
                case 3:
                    /////// 3rd down and up
                    randomNumber = marsenneTwister() % 70 + 40;
                    Thread::sleep(randomNumber);
                    randomNumber = marsenneTwister() % 20 + 1;
                    ScratchFrequencyDown();
                    AmpLevelDown();
                    randomNumber = marsenneTwister() % 40 + 50;
                    Thread::sleep(randomNumber);
                    AmpLevelUp();
                    randomNumber = marsenneTwister() % 10 + 1;
                    ScratchFrequencyUp();
                    break;
                    
                default:
                    randomNumber = marsenneTwister() % 1000;
                    AmpLevelDown();
                    randomNumber = marsenneTwister() % 300;
                    Thread::sleep(randomNumber);
                    AmpLevelUp();
                    Thread::sleep(randomNumber);
                    AmpLevelDown();
                    randomNumber = marsenneTwister() % 40 + 50;
                    Thread::sleep(randomNumber);
                    AmpLevelUp();
                    randomNumber = marsenneTwister() % 50 + 20;
                    Thread::sleep(randomNumber);
                    AmpLevelDown();
                    randomNumber = marsenneTwister() % 70 + 100;
                    Thread::sleep(randomNumber);
                    AmpLevelUp();
                    randomNumber = marsenneTwister() % 300;
                    Thread::sleep(randomNumber);
                    AmpLevelDown();
                    randomNumber = marsenneTwister() % 200 + 50;
                    Thread::sleep(randomNumber);
                    AmpLevelUp();
                    break;
            }
        }
    };
    //                                                  itch button
    m_editor->m_Itch.onClick = [this]
    {
        
        triPreviousAmp = m_processor->m_triangleAmp;
        sawPreviousAmp = m_processor->m_sawAmp;
        sawInvPreviousAmp = m_processor->m_sawInvertedAmp;
        sinePreviousAmp = m_processor->m_sineAmp;
        squPreviousAmp = m_processor->m_squareAmp;

        
        triPreviousAmpCopy = m_processor->m_triangleAmp;
        sawPreviousAmpCopy = m_processor->m_sawAmp;
        sawInvPreviousAmpCopy = m_processor->m_sawInvertedAmp;
        sinePreviousAmpCopy = m_processor->m_sineAmp;
        squPreviousAmpCopy = m_processor->m_squareAmp;
        
        triangleState = m_processor->m_triangleSelector;
        sawState = m_processor->m_sawSelector;
        sawInvState = m_processor->m_sawInvertedSelector;
        squState = m_processor->m_squareSelector;
        sineState = m_processor->m_sineSelector;

        
        std::random_device RD;
        std::mt19937 marsenneTwister(RD());
        randomNumber = marsenneTwister() % 500;
        
        // cant get delay plugin working, so this....
        
        forLoopRandomizer = marsenneTwister() % 20 + 1;
        
        for (int i = 0; i < forLoopRandomizer; i++) {
            AmpLevelDown();
            
            triPreviousAmp *= 0.9;
            sawPreviousAmp *= 0.9;
            sawInvPreviousAmp *= 0.9;
            sinePreviousAmp *= 0.9;
            squPreviousAmp *= 0.9;
            
            
            m_switcher = marsenneTwister() % 4 + 1;
            switch (m_switcher) {
                case 1:
                    
                    
                    if(!m_processor->m_triangleSelector)
                        m_processor->m_triangleSelector = true;
                    else
                        m_processor->m_triangleSelector = false;
                    
                    
                    if(!m_processor->m_sawSelector)
                        m_processor->m_sawSelector = true;
                    else
                        m_processor->m_sawSelector = false;
                    
                    if(!m_processor->m_squareSelector)
                        m_processor->m_squareSelector = true;
                    else
                        m_processor->m_squareSelector = false;
                    
                    break;
                    
                case 2:
                    
                    
                    if(!m_processor->m_sineSelector)
                        m_processor->m_sineSelector = true;
                    else
                        m_processor->m_sineSelector = false;
                    
                    
                    
                    if(!m_processor->m_squareSelector)
                        m_processor->m_squareSelector = true;
                    else
                        m_processor->m_squareSelector = false;
                    
                    
                    break;
                    
                case 3:
                    
                    
                    
                    if(!m_processor->m_sawInvertedSelector)
                        m_processor->m_sawInvertedSelector = true;
                    else
                        m_processor->m_sawInvertedSelector = false;
                    
                    
                    
                    if(!m_processor->m_sawSelector)
                        m_processor->m_sawSelector = true;
                    else
                        m_processor->m_sawSelector = false;
                    
                    
                    
                    if(!m_processor->m_squareSelector)
                        m_processor->m_squareSelector = true;
                    else
                        m_processor->m_squareSelector = false;
                    
                    
                    if(!m_processor->m_triangleSelector)
                        m_processor->m_triangleSelector = true;
                    else
                        m_processor->m_triangleSelector = false;
                    
                    
                    break;
                    
                default:
                    
                    
                    
                    if(!m_processor->m_sawInvertedSelector)
                        m_processor->m_sawInvertedSelector = true;
                    else
                        m_processor->m_sawInvertedSelector = false;
                    
                    
                    
                    if(!m_processor->m_sawSelector)
                        m_processor->m_sawSelector = true;
                    else
                        m_processor->m_sawSelector = false;
                    
                    
                    break;
            }
            
            
            
            randomNumber = marsenneTwister() % 50;
            randomNumber += 50;
            Thread::sleep(randomNumber);
            
            AmpLevelUp();
            randomNumber = marsenneTwister() % 100 + 50;
            
            Thread::sleep(randomNumber);
        }
        
        AmpLevelDown();
        
        
        randomNumber = marsenneTwister() % 50 + 5;
        
        Thread::sleep(randomNumber);
        
        triPreviousAmp = triPreviousAmpCopy;
        sawPreviousAmp = sawPreviousAmpCopy;
        sawInvPreviousAmp = sawInvPreviousAmpCopy;
        sinePreviousAmp = sinePreviousAmpCopy;
        squPreviousAmp = squPreviousAmpCopy;
        
        forLoopRandomizer = marsenneTwister() % 20 + 1;
        
        for (int i = 0; i < forLoopRandomizer; i++) {
            AmpLevelDown();
            
            triPreviousAmp *= 0.9;
            sawPreviousAmp *= 0.9;
            sawInvPreviousAmp *= 0.9;
            sinePreviousAmp *= 0.9;
            squPreviousAmp *= 0.9;
            
            
            m_switcher = marsenneTwister() % 4 + 1;
            switch (m_switcher) {
                case 1:
                    
                    
                    if(!m_processor->m_triangleSelector)
                        m_processor->m_triangleSelector = true;
                    else
                        m_processor->m_triangleSelector = false;
                    
                    if(!m_processor->m_sawInvertedSelector)
                        m_processor->m_sawInvertedSelector = true;
                    else
                        m_processor->m_sawInvertedSelector = false;
                    
                    
                    
                    if(!m_processor->m_sawSelector)
                        m_processor->m_sawSelector = true;
                    else
                        m_processor->m_sawSelector = false;
                    
                    
                    break;
                    
                case 2:
                    
                    
                    if(!m_processor->m_sineSelector)
                        m_processor->m_sineSelector = true;
                    else
                        m_processor->m_sineSelector = false;
                    
                    
                    
                    if(!m_processor->m_squareSelector)
                        m_processor->m_squareSelector = true;
                    else
                        m_processor->m_squareSelector = false;
                    
                    
                    break;
                    
                case 3:
                    
                    
                    
                    if(!m_processor->m_sawInvertedSelector)
                        m_processor->m_sawInvertedSelector = true;
                    else
                        m_processor->m_sawInvertedSelector = false;
                    
                    
                    
                    if(!m_processor->m_sawSelector)
                        m_processor->m_sawSelector = true;
                    else
                        m_processor->m_sawSelector = false;
                    
                    
                    
                    if(!m_processor->m_squareSelector)
                        m_processor->m_squareSelector = true;
                    else
                        m_processor->m_squareSelector = false;
                    
                    break;
                    
                default:
                    
                    
                    if(!m_processor->m_sawSelector)
                        m_processor->m_sawSelector = true;
                    else
                        m_processor->m_sawSelector = false;
                    
                    if(!m_processor->m_squareSelector)
                        m_processor->m_squareSelector = true;
                    else
                        m_processor->m_squareSelector = false;
                    
                    
                    if(!m_processor->m_sawInvertedSelector)
                        m_processor->m_sawInvertedSelector = true;
                    else
                        m_processor->m_sawInvertedSelector = false;
                    
                    if(!m_processor->m_triangleSelector)
                        m_processor->m_triangleSelector = true;
                    else
                        m_processor->m_triangleSelector = false;
                    
                    
                    
                break;  }
            
            randomNumber = marsenneTwister() % 50;
            randomNumber += 50;
            Thread::sleep(randomNumber);
            
            AmpLevelUp();
            randomNumber = marsenneTwister() % 100 + 50;
            
            Thread::sleep(randomNumber);
        }
        
        AmpLevelDown();
        
        
        randomNumber = marsenneTwister() % 50 + 5;
        
        Thread::sleep(randomNumber);
        
        triPreviousAmp = triPreviousAmpCopy;
        sawPreviousAmp = sawPreviousAmpCopy;
        sawInvPreviousAmp = sawInvPreviousAmpCopy;
        sinePreviousAmp = sinePreviousAmpCopy;
        squPreviousAmp = squPreviousAmpCopy;
        

        m_processor->m_triangleSelector = triangleState;
        m_processor->m_sawSelector = sawState;
        m_processor->m_sawInvertedSelector = sawInvState;
        m_processor->m_squareSelector = squState;
        m_processor->m_sineSelector = sineState;
        
        AmpLevelUp();


    };
    //                                                              garble button
    m_editor->m_Garble.onClick = [this]     {
        
        
        triPreviousAmp = m_processor->m_triangleAmp;
        sawPreviousAmp = m_processor->m_sawAmp;
        sawInvPreviousAmp = m_processor->m_sawInvertedAmp;
        sinePreviousAmp = m_processor->m_sineAmp;
        squPreviousAmp = m_processor->m_squareAmp;
        
        
        triPreviousAmpCopy = m_processor->m_triangleAmp;
        sawPreviousAmpCopy = m_processor->m_sawAmp;
        sawInvPreviousAmpCopy = m_processor->m_sawInvertedAmp;
        sinePreviousAmpCopy = m_processor->m_sineAmp;
        squPreviousAmpCopy = m_processor->m_squareAmp;
        
        
        std::random_device RD;
        std::mt19937 marsenneTwister(RD());
        randomNumber = marsenneTwister() % 5;
        randomNumber += 2;
        
        forLoopRandomizer = marsenneTwister() % 5 + 1;
        forLoopRandomizerNested = marsenneTwister() % 15 + 1;
        
        for (int i = 0; i < forLoopRandomizer; i++) {
            for (int i = 0; i < forLoopRandomizerNested; i++) {
                AmpLevelDown();
                
                triPreviousAmp *= 0.95;
                sawPreviousAmp *= 0.95;
                sawInvPreviousAmp *= 0.95;
                sinePreviousAmp *= 0.95;
                squPreviousAmp *= 0.95;
                
                randomNumber = marsenneTwister() % 20;
                randomNumber += 20;
                Thread::sleep(randomNumber);
                
                AmpLevelUp();
                randomNumber = marsenneTwister() % 10 + 20;
                
                Thread::sleep(randomNumber);
            }
            triPreviousAmp = triPreviousAmpCopy;
            sawPreviousAmp = sawPreviousAmpCopy;
            sawInvPreviousAmp = sawInvPreviousAmpCopy;
            sinePreviousAmp = sinePreviousAmpCopy;
            squPreviousAmp = squPreviousAmpCopy;
            AmpLevelUp();
        }
        
    };
    
    //                                                              gobble button
    m_editor->m_Gobble.onClick = [this]     {
        
        triPreviousFreq = m_processor->WaveTableTri.getFreq();
        sawPreviousFreq = m_processor->WaveTableSaw.getFreq();
        sawInvPreviousFreq = m_processor->WaveTableSawInv.getFreq();
        sinePreviousFreq = m_processor->WaveTableSine.getFreq();
        squPreviousFreq = m_processor->WaveTableSqu.getFreq();
        
        triPreviousAmp = m_processor->m_triangleAmp;
        sawPreviousAmp = m_processor->m_sawAmp;
        sawInvPreviousAmp = m_processor->m_sawInvertedAmp;
        sinePreviousAmp = m_processor->m_sineAmp;
        squPreviousAmp = m_processor->m_squareAmp;
        
        
        triPreviousAmpCopy = m_processor->m_triangleAmp;
        sawPreviousAmpCopy = m_processor->m_sawAmp;
        sawInvPreviousAmpCopy = m_processor->m_sawInvertedAmp;
        sinePreviousAmpCopy = m_processor->m_sineAmp;
        squPreviousAmpCopy = m_processor->m_squareAmp;
        
        
        std::random_device RD;
        std::mt19937 marsenneTwister(RD());
        randomNumber = marsenneTwister() % 5;
        randomNumber += 2;
        
        forLoopRandomizer = marsenneTwister() % 5 + 2;
        forLoopRandomizerNested = marsenneTwister() % 10 + 7;
        
        for (int i = 0; i < forLoopRandomizer; i++) {
            for (int i = 0; i < forLoopRandomizerNested; i++) {
                
                AmpLevelDown();
                randomNumber = marsenneTwister() % 20;
                
                Thread::sleep(randomNumber);
                
                triFreq = m_processor->WaveTableTri.getFreq();
                m_processor->WaveTableTri.setFreq(triFreq *= 0.95);
                m_processor->WaveTableTri.setSampleRate(m_processor->getSampleRate());
                
                sawFreq = m_processor->WaveTableSaw.getFreq();
                m_processor->WaveTableSaw.setFreq(sawFreq *= 0.95);
                m_processor->WaveTableSaw.setSampleRate(m_processor->getSampleRate());
                
                sawInvFreq = m_processor->WaveTableSawInv.getFreq();
                m_processor->WaveTableSawInv.setFreq(sawInvFreq *= 0.95);
                m_processor->WaveTableSawInv.setSampleRate(m_processor->getSampleRate());
                
                sineFreq = m_processor->WaveTableSine.getFreq();
                m_processor->WaveTableSine.setFreq(sineFreq *= 0.95);
                m_processor->WaveTableSine.setSampleRate(m_processor->getSampleRate());
                
                squFreq = m_processor->WaveTableSqu.getFreq();
                m_processor->WaveTableSqu.setFreq(squFreq *= 0.95);
                m_processor->WaveTableSqu.setSampleRate(m_processor->getSampleRate());
                
                triPreviousAmp *= 0.9;
                sawPreviousAmp *= 0.9;
                sawInvPreviousAmp *= 0.9;
                sinePreviousAmp *= 0.9;
                squPreviousAmp *= 0.9;
                
                AmpLevelUp();
                randomNumber = marsenneTwister() % 10 + 20;
                
                Thread::sleep(randomNumber);
            }
            triPreviousAmp = triPreviousAmpCopy;
            sawPreviousAmp = sawPreviousAmpCopy;
            sawInvPreviousAmp = sawInvPreviousAmpCopy;
            sinePreviousAmp = sinePreviousAmpCopy;
            squPreviousAmp = squPreviousAmpCopy;
            
            AmpLevelUp();
            
            m_processor->WaveTableTri.setFreq(triPreviousFreq);
            
            
            m_processor->WaveTableSaw.setFreq(sawPreviousFreq);
            
            
            m_processor->WaveTableSawInv.setFreq(sawInvPreviousFreq);
            
            
            m_processor->WaveTableSine.setFreq(sinePreviousFreq);
            
            
            m_processor->WaveTableSqu.setFreq(squPreviousFreq);
            
            m_processor->WaveTableTri.setSampleRate(m_processor->getSampleRate());
            
            
            m_processor->WaveTableSaw.setSampleRate(m_processor->getSampleRate());
            
            
            m_processor->WaveTableSawInv.setSampleRate(m_processor->getSampleRate());
            
            
            m_processor->WaveTableSine.setSampleRate(m_processor->getSampleRate());
            
            
            m_processor->WaveTableSqu.setSampleRate(m_processor->getSampleRate());
        }
        
    };
    
    
}










PluginController::~PluginController(){
}


void PluginController::ScratchFrequencyDown(){
    //freq
    while (m_processor->WaveTableTri.getFreq() > 0.0f || m_processor->WaveTableSaw.getFreq() > 0.0f || m_processor->WaveTableSawInv.getFreq() > 0.0f || m_processor->WaveTableSine.getFreq() > 0.0f || m_processor->WaveTableSqu.getFreq() > 0.0f) {
        Thread::sleep(randomNumber);
        triFreq = m_processor->WaveTableTri.getFreq();
        m_processor->WaveTableTri.setFreq(triFreq *= 0.8);
        m_processor->WaveTableTri.setSampleRate(m_processor->getSampleRate());
        if (m_processor->WaveTableTri.getFreq() <= 20) {
            m_processor->WaveTableTri.setFreq(0);
        }
        sawFreq = m_processor->WaveTableSaw.getFreq();
        m_processor->WaveTableSaw.setFreq(sawFreq *= 0.8);
        m_processor->WaveTableSaw.setSampleRate(m_processor->getSampleRate());
        if (m_processor->WaveTableSaw.getFreq() <= 20) {
            m_processor->WaveTableSaw.setFreq(0);
        }
        sawInvFreq = m_processor->WaveTableSawInv.getFreq();
        m_processor->WaveTableSawInv.setFreq(sawInvFreq *= 0.8);
        m_processor->WaveTableSawInv.setSampleRate(m_processor->getSampleRate());
        if (m_processor->WaveTableSawInv.getFreq() <= 20) {
            m_processor->WaveTableSawInv.setFreq(0);
        }
        sineFreq = m_processor->WaveTableSine.getFreq();
        m_processor->WaveTableSine.setFreq(sineFreq *= 0.8);
        m_processor->WaveTableSine.setSampleRate(m_processor->getSampleRate());
        if (m_processor->WaveTableSine.getFreq() <= 20) {
            m_processor->WaveTableSine.setFreq(0);
        }
        squFreq = m_processor->WaveTableSqu.getFreq();
        m_processor->WaveTableSqu.setFreq(squFreq *= 0.8);
        m_processor->WaveTableSqu.setSampleRate(m_processor->getSampleRate());
        if (m_processor->WaveTableSqu.getFreq() <= 20) {
            m_processor->WaveTableSqu.setFreq(0);
        }
    }
}


void PluginController::ScratchFrequencyUp(){
    //freq up to previous rate
    while (m_processor->WaveTableTri.getFreq() < triPreviousFreq || m_processor->WaveTableSaw.getFreq() < sawPreviousFreq || m_processor->WaveTableSawInv.getFreq() < sawInvPreviousFreq || m_processor->WaveTableSine.getFreq() < sinePreviousFreq || m_processor->WaveTableSqu.getFreq() < squPreviousFreq) {
        Thread::sleep(randomNumber);
        triFreq = m_processor->WaveTableTri.getFreq();
        m_processor->WaveTableTri.setFreq(triFreq += 3);
        m_processor->WaveTableTri.setFreq(triFreq *= 1.2);
        m_processor->WaveTableTri.setSampleRate(m_processor->getSampleRate());
        if (m_processor->WaveTableTri.getFreq() > triPreviousFreq) {
            m_processor->WaveTableTri.setFreq(triPreviousFreq);         
            m_processor->WaveTableTri.setSampleRate(m_processor->getSampleRate());
        }
        sawFreq = m_processor->WaveTableSaw.getFreq();
        m_processor->WaveTableSaw.setFreq(sawFreq += 3);
        m_processor->WaveTableSaw.setFreq(sawFreq *= 1.2);
        m_processor->WaveTableSaw.setSampleRate(m_processor->getSampleRate());
        if (m_processor->WaveTableSaw.getFreq() > sawPreviousFreq) {
            m_processor->WaveTableSaw.setFreq(sawPreviousFreq);
            m_processor->WaveTableSaw.setSampleRate(m_processor->getSampleRate());
        }
        sawInvFreq = m_processor->WaveTableSawInv.getFreq();
        m_processor->WaveTableSawInv.setFreq(sawInvFreq += 3);
        m_processor->WaveTableSawInv.setFreq(sawInvFreq *= 1.2);
        m_processor->WaveTableSawInv.setSampleRate(m_processor->getSampleRate());
        if (m_processor->WaveTableSawInv.getFreq() > sawInvPreviousFreq) {
            m_processor->WaveTableSawInv.setFreq(sawInvPreviousFreq);
            m_processor->WaveTableSawInv.setSampleRate(m_processor->getSampleRate());
        }
        sineFreq = m_processor->WaveTableSine.getFreq();
        m_processor->WaveTableSine.setFreq(sineFreq += 3);
        m_processor->WaveTableSine.setFreq(sineFreq *= 1.2);
        m_processor->WaveTableSine.setSampleRate(m_processor->getSampleRate());
        if (m_processor->WaveTableSine.getFreq() > sinePreviousFreq) {
            m_processor->WaveTableSine.setFreq(sinePreviousFreq);
            m_processor->WaveTableSine.setSampleRate(m_processor->getSampleRate());
        }
        squFreq = m_processor->WaveTableSqu.getFreq();
        m_processor->WaveTableSqu.setFreq(squFreq += 3);
        m_processor->WaveTableSqu.setFreq(squFreq *= 1.2);
        m_processor->WaveTableSqu.setSampleRate(m_processor->getSampleRate());
        if (m_processor->WaveTableSqu.getFreq() > squPreviousFreq) {
            m_processor->WaveTableSqu.setFreq(squPreviousFreq);
            m_processor->WaveTableSqu.setSampleRate(m_processor->getSampleRate());
        }
    }
}


void PluginController::AmpLevelDown(){
    //amp
    while (m_processor->m_triangleAmp > 0.0f || m_processor->m_sawAmp > 0.0f || m_processor->m_sawInvertedAmp > 0.0f || m_processor->m_sineAmp > 0.0f || m_processor->m_squareAmp > 0.0f) {
        m_processor->m_triangleAmp *= 0.9;
        if (m_processor->m_triangleAmp <= 0.05) {
            m_processor->m_triangleAmp = 0;
        }
        
        m_processor->m_sawAmp *= 0.9;
        if (m_processor->m_sawAmp <= 0.05) {
            m_processor->m_sawAmp = 0;
        }
        
        m_processor->m_sawInvertedAmp *= 0.9;
        if (m_processor->m_sawInvertedAmp <= 0.05) {
            m_processor->m_sawInvertedAmp = 0;
        }
        
        m_processor->m_sineAmp *= 0.9;
        if (m_processor->m_sineAmp <= 0.05) {
            m_processor->m_sineAmp = 0;
        }
        
        m_processor->m_squareAmp *= 0.9;
        if (m_processor->m_squareAmp <= 0.05) {
            m_processor->m_squareAmp = 0;
        }
    }
}


void PluginController::AmpLevelUp(){
    //amp back up to previous level
    while (m_processor->m_triangleAmp < triPreviousAmp || m_processor->m_sawAmp < sawPreviousAmp || m_processor->m_sawInvertedAmp < sawInvPreviousAmp || m_processor->m_sineAmp < sinePreviousAmp || m_processor->m_squareAmp < squPreviousAmp) {
        m_processor->m_triangleAmp += 0.1;
        if (m_processor->m_triangleAmp > triPreviousAmp) {
            m_processor->m_triangleAmp = triPreviousAmp;
        }
        
        m_processor->m_sawAmp += 0.1;
        if (m_processor->m_sawAmp > sawPreviousAmp) {
            m_processor->m_sawAmp = sawPreviousAmp;
        }
        
        m_processor->m_sawInvertedAmp += 0.1;
        if (m_processor->m_sawInvertedAmp > sawInvPreviousAmp) {
            m_processor->m_sawInvertedAmp = sawInvPreviousAmp;
        }
        
        m_processor->m_sineAmp += 0.1;
        if (m_processor->m_sineAmp > sinePreviousAmp) {
            m_processor->m_sineAmp = sinePreviousAmp;
        }
        
        m_processor->m_squareAmp += 0.1;
        if (m_processor->m_squareAmp > squPreviousAmp) {
            m_processor->m_squareAmp = squPreviousAmp;
        }
    }
}
