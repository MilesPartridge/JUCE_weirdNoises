/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WeirdNoisesAudioProcessorEditor::WeirdNoisesAudioProcessorEditor (WeirdNoisesAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), m_controller(this, &p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    
    setLookAndFeel (&m_lookAndFeelMiles);
    
    
    m_buttonTriangle.setButtonText ("Triangle");
    addAndMakeVisible (m_buttonTriangle);
    
    m_buttonSquare.setButtonText ("Square");
    addAndMakeVisible (m_buttonSquare);
    
    m_buttonSine.setButtonText ("Sine");
    addAndMakeVisible (m_buttonSine);
    
    m_buttonSaw.setButtonText ("Saw");
    addAndMakeVisible (m_buttonSaw);
    
    m_buttonInvertedSaw.setButtonText ("Inverted Saw");
    addAndMakeVisible (m_buttonInvertedSaw);
    
    m_Scratch.setButtonText ("Scratch It!");
    m_Scratch.setAlpha(0.75);
    addAndMakeVisible (m_Scratch);
    
    m_Itch.setButtonText ("Itch It!");
    m_Itch.setAlpha(0.75);
    addAndMakeVisible (m_Itch);
    
    m_Garble.setButtonText ("Garble It!");
    m_Garble.setAlpha(0.75);
    addAndMakeVisible (m_Garble);
    
    m_Gobble.setButtonText ("Gobble It!");
    m_Gobble.setAlpha(0.75);
    addAndMakeVisible (m_Gobble);
    
    
    m_PWM_Slider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    m_PWM_Slider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    m_PWM_Slider.setRange(35, wave_table.getSize() - 35);
    m_PWM_Slider.setValue(wave_table.getSize()/2);
    m_PWM_Slider.setNumDecimalPlacesToDisplay(0);
    m_PWM_Slider.setTextValueSuffix("PWM");
    addAndMakeVisible(m_PWM_Slider);
    
    m_cutoffSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    m_cutoffSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    m_cutoffSlider.setRange(0, 0.99);
    m_cutoffSlider.setValue(0.5);
    m_cutoffSlider.setTextValueSuffix("cutoff");
    addAndMakeVisible(m_cutoffSlider);
    
    
    /////////////////                                                   amount rotary knobs
    
    m_triAmountSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    m_triAmountSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    m_triAmountSlider.setRange(0, 0.99);
    m_triAmountSlider.setValue(0.5);
    m_triAmountSlider.setTextValueSuffix("triAmount");
    m_triAmountSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(m_triAmountSlider);
    
    m_sineAmountSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    m_sineAmountSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    m_sineAmountSlider.setRange(0, 0.99);
    m_sineAmountSlider.setValue(0.5);
    m_sineAmountSlider.setTextValueSuffix("sineAmount");
    m_sineAmountSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(m_sineAmountSlider);
    
    m_sawAmountSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    m_sawAmountSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    m_sawAmountSlider.setRange(0, 0.99);
    m_sawAmountSlider.setValue(0.5);
    m_sawAmountSlider.setTextValueSuffix("sawAmount");
    m_sawAmountSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(m_sawAmountSlider);
    
    m_sawInvAmountSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    m_sawInvAmountSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    m_sawInvAmountSlider.setRange(0, 0.99);
    m_sawInvAmountSlider.setValue(0.5);
    m_sawInvAmountSlider.setTextValueSuffix("sawInvAmount");
    m_sawInvAmountSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(m_sawInvAmountSlider);
    
    m_squAmountSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    m_squAmountSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    m_squAmountSlider.setRange(0, 0.99);
    m_squAmountSlider.setValue(0.5);
    m_squAmountSlider.setTextValueSuffix("squAmount");
    m_squAmountSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(m_squAmountSlider);
    
    
    
    ///////////////                                                         frequency rotary knobs
    
    m_triFreqSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    m_triFreqSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    m_triFreqSlider.setRange(20, 3000);
    m_triFreqSlider.setValue(190);
    m_triFreqSlider.setTextValueSuffix("triFreq");
    m_triFreqSlider.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(m_triFreqSlider);
    
    m_sineFreqSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    m_sineFreqSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    m_sineFreqSlider.setRange(20, 3000);
    m_sineFreqSlider.setValue(190);
    m_sineFreqSlider.setTextValueSuffix("sineFreq");
    m_sineFreqSlider.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(m_sineFreqSlider);
    
    m_sawFreqSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    m_sawFreqSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    m_sawFreqSlider.setRange(20, 3000);
    m_sawFreqSlider.setValue(190);
    m_sawFreqSlider.setTextValueSuffix("sawFreq");
    m_sawFreqSlider.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(m_sawFreqSlider);
    
    m_sawInvFreqSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    m_sawInvFreqSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    m_sawInvFreqSlider.setRange(20, 3000);
    m_sawInvFreqSlider.setValue(190);
    m_sawInvFreqSlider.setTextValueSuffix("sawInvFreq");
    m_sawInvFreqSlider.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(m_sawInvFreqSlider);
    
    m_squFreqSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    m_squFreqSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    m_squFreqSlider.setRange(20, 3000);
    m_squFreqSlider.setValue(190);
    m_squFreqSlider.setTextValueSuffix("squFreq");
    m_squFreqSlider.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(m_squFreqSlider);
    
    
}

WeirdNoisesAudioProcessorEditor::~WeirdNoisesAudioProcessorEditor()
{
    setLookAndFeel (nullptr);
}

//==============================================================================
void WeirdNoisesAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::grey);

    g.setColour (Colours::springgreen);
    g.setFont (15.0f);
    g.drawFittedText ("Weird Noises", getLocalBounds().removeFromTop(10), Justification::centred, 1);
    
    g.fillAll (Colours::darkgrey);
}

void WeirdNoisesAudioProcessorEditor::resized()
{
    int totalX = 800;
    int totalY = 600;
    int box_X = totalX * 0.5;
    int box_Y = totalY / 9;
    int spacer = 15;
    
    m_buttonTriangle.setBounds(spacer, spacer, box_X, box_Y);
    m_triAmountSlider.setBounds(box_X, spacer, box_X*0.5, box_Y);
    m_triFreqSlider.setBounds(box_X*1.5, spacer, box_X*0.5, box_Y);
    
    m_buttonSine.setBounds (spacer, spacer*2 + box_Y, box_X, box_Y);
    m_sineAmountSlider.setBounds(box_X, spacer*2 + box_Y, box_X*0.5, box_Y);
    m_sineFreqSlider.setBounds(box_X*1.5, spacer*2 + box_Y, box_X*0.5, box_Y);
    
    m_buttonSaw.setBounds (spacer, spacer*3 + box_Y*2, box_X, box_Y);
    m_sawAmountSlider.setBounds(box_X, spacer*3 + box_Y*2, box_X*0.5, box_Y);
    m_sawFreqSlider.setBounds(box_X*1.5, spacer*3 + box_Y*2, box_X*0.5, box_Y);
    
    m_buttonInvertedSaw.setBounds (spacer, spacer*4 + box_Y*3, box_X, box_Y);
    m_sawInvAmountSlider.setBounds(box_X, spacer*4 + box_Y*3, box_X*0.5, box_Y);
    m_sawInvFreqSlider.setBounds(box_X*1.5, spacer*4 + box_Y*3, box_X*0.5, box_Y);
    
    m_buttonSquare.setBounds (spacer, spacer*5 + box_Y*4, box_X, box_Y);
    m_squAmountSlider.setBounds(box_X, spacer*5 + box_Y*4, box_X*0.5, box_Y);
    m_squFreqSlider.setBounds(box_X*1.5, spacer*5 + box_Y*4, box_X*0.5, box_Y);
    
    m_PWM_Slider.setBounds(spacer, spacer*5 + box_Y*5, totalX - spacer*2, spacer*2);
    
    m_Itch.setBounds (spacer, spacer*8 + box_Y*5, box_X - spacer*2, box_Y);
    m_Scratch.setBounds (spacer + box_X, spacer*8 + box_Y*5, box_X - spacer*2, box_Y);
    m_Garble.setBounds (spacer, spacer*8.5 + box_Y*6, box_X - spacer*2, box_Y);
    m_Gobble.setBounds (spacer + box_X, spacer*8.5 + box_Y*6, box_X - spacer*2, box_Y);
    
}
