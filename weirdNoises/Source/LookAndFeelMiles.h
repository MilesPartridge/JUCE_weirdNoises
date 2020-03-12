/*
  ==============================================================================

    LookAndFeelMiles.h
    Created: 12 Mar 2019 7:18:06am
    Author:  Miles Partridge

  ==============================================================================
*/

#pragma once
/////////////                               from Juce tutorial
class LookAndFeelMiles : public LookAndFeel_V4
{
public:
    LookAndFeelMiles()
    {
        setColour (Slider::thumbColourId, Colours::springgreen);
    }
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        auto radius = jmin (width / 2, height / 2) - 4.0f;
        auto centreX = x + width  * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        // fill
        g.setColour (Colours::darkgreen);
        g.fillEllipse (rx, ry, rw, rw);
        
        // outline
        g.setColour (Colours::green);
        g.drawEllipse (rx, ry, rw, rw, 1.0f);
        
        Path p;
        auto pointerLength = radius * 0.33f;
        auto pointerThickness = 2.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        
        // pointer
        g.setColour (Colours::palegreen);
        g.fillPath (p);
        
    }
    
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override
    {
        auto buttonArea = button.getLocalBounds();
        auto edge = 4;
        
        buttonArea.removeFromLeft (edge);
        buttonArea.removeFromTop (edge);
        
        // shadow
        g.setColour (Colours::darkgreen.withAlpha (0.5f));
        g.fillRect (buttonArea);
        
        auto offset = isButtonDown ? -edge / 2 : -edge;
        buttonArea.translate (offset, offset);
        
        g.setColour (Colours::black);
        g.fillRect (buttonArea);
    }
    
    void drawButtonText (Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) override
    {
        auto font = getTextButtonFont (button, button.getHeight());
        g.setFont (font);
        g.setColour (Colours::springgreen);
        
        auto yIndent = jmin (4, button.proportionOfHeight (0.3f));
        auto cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;
        
        auto fontHeight = roundToInt (font.getHeight() * 0.6f);
        auto leftIndent  = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft()  ? 4 : 2));
        auto rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
        auto textWidth = button.getWidth() - leftIndent - rightIndent;
        
        auto edge = 4;
        auto offset = isButtonDown ? edge / 2 : 0;
        
        if (textWidth > 0)
            g.drawFittedText (button.getButtonText(),
                              leftIndent + offset, yIndent + offset, textWidth, button.getHeight() - yIndent * 2 - edge,
                              Justification::centred, 2);
    }
    
};

