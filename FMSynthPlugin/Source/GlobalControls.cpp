/*
  ==============================================================================

    GlobalControls.cpp
    Created: 4 Sep 2022 9:21:55pm
    Author:  Joshua Cann

  ==============================================================================
*/

#include "GlobalControls.h"

void MyButton::paint(Graphics& g)
{
    isButtonOn() ? g.setColour(Colours::darkgreen) : g.setColour(Colours::darkred);
    
    if(isOnComponent()) {
        if(isButtonOn())
            g.setColour(Colours::darkseagreen);
        if(!isButtonOn())
            g.setColour(Colours::deeppink);
    }

    if(buttonIsDown()) {
        if(isButtonOn())
            g.setColour(Colours::darkkhaki);
        if(!isButtonOn())
            g.setColour(Colours::red);
    }
    
    g.fillRect(0, 0, getWidth(), getHeight());
    
    g.setColour(Colours::black);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 4, 4);
    g.setColour(Colours::white);
    g.drawText(labelText, getWidth() / 3, 0, getWidth(), getHeight(), NotificationType::dontSendNotification);
    
//    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 4, 1);
//    needsRepaint = false;
}

void MyButton::mouseUpdate()
{
    
    if(isButtonOn())
        labelText = "FM On";
    else
        labelText = "FM Off";
    repaint();
}

GlobalControls::GlobalControls()
{
    addAndMakeVisible(label);
    
    addAndMakeVisible(filterCutoff);
    filterCutoff.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    filterCutoff.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, filterCutoff.getTextBoxWidth(), filterCutoff.getTextBoxHeight());
    filterCutoff.setRange(0.001, 0.7, 0.001);
    filterCutoff.setValue(0.3);
//    filterCutoff.setTextValueSuffix("Hz");
    addAndMakeVisible(cutoffLabel);
    cutoffLabel.setText("Filter Cutoff", NotificationType::dontSendNotification);
    cutoffLabel.attachToComponent(&filterCutoff, false);
    
    addAndMakeVisible(masterVolume);
    masterVolume.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    masterVolume.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, masterVolume.getTextBoxWidth(), masterVolume.getTextBoxHeight());
    masterVolume.setRange(-60, 0, 0.01);
    masterVolume.setValue(-6);
    masterVolume.setTextValueSuffix("dB");
    addAndMakeVisible(volumeLabel);
    volumeLabel.setText("Master Volume", NotificationType::dontSendNotification);
    volumeLabel.attachToComponent(&masterVolume, false);
    
    addAndMakeVisible(FMTone);
    FMTone.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    FMTone.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, FMTone.getTextBoxWidth() * 0.5, FMTone.getTextBoxHeight() * 0.75);
    FMTone.setRange(0, 100, 1);
    FMTone.setValue(30);
    FMTone.setTextValueSuffix("%");
    addAndMakeVisible(FMToneLabel);
    FMToneLabel.setText("FM Tone", NotificationType::dontSendNotification);
    FMToneLabel.attachToComponent(&FMTone, false);
    
    label.setText("Global Controls", NotificationType::dontSendNotification);
//    addAndMakeVisible(FMToggle);
}

void GlobalControls::paint(Graphics& g)
{
    label.setBounds(0, 0, getWidth(), getHeight() * 0.2);
    
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight() * 0.2, 5);
    g.drawRect(0, 0, getWidth() / 1.5, getHeight(), 3);
    g.drawRect(getWidth() / 1.5, 0, getWidth() / 3, getHeight(), 3);
    
    g.setColour(Colours::white);
    
    filterCutoff.setBounds(5, getHeight() * 0.375, getWidth() * 0.3, getWidth() * 0.3);
    masterVolume.setBounds(getWidth() / 3 + 5, getHeight() * 0.375, getWidth() * 0.3, getWidth() * 0.3);
    FMTone.setBounds(getWidth() / 1.375, getHeight() * 0.55, getWidth() * 0.2, getWidth() * 0.2);
    
    FMToggle.setBounds(getWidth() / 1.5, getHeight() * 0.2, getWidth() / 3, getHeight() * 0.2);
}
