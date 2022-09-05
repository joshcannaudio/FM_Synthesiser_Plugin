/*
  ==============================================================================

    OscillatorComponent.cpp
    Created: 4 Sep 2022 4:11:09pm
    Author:  Joshua Cann

  ==============================================================================
*/

#include "OscillatorComponent.h"

OscillatorComponent::OscillatorComponent()
{  // What ever is made visible last is the top layer !!!
    addAndMakeVisible(powerButton);
    addAndMakeVisible(oscName);

    addAndMakeVisible(waveTypeBox);
    waveTypeBox.addItemList(waves, 1); // may need to add listener to interact
    waveTypeBox.setSelectedItemIndex(0);
    
    float defaultEnvValues[4] = { 0.1, 0.5, 0.4, 0.2 };
    for(int i = 0; i < 4; i++) {
        addAndMakeVisible(envelopeSlider[i]); // env sliders
        envelopeSlider[i].setSliderStyle(Slider::SliderStyle::LinearVertical);
        envelopeSlider[i].setRange(0.0, 3, 0.001);
        envelopeSlider[i].setTextBoxStyle(Slider::TextBoxBelow, false, envelopeSlider[i].getTextBoxWidth(), envelopeSlider[i].getTextBoxHeight());
        envelopeSlider[i].setValue(defaultEnvValues[i]);
    }
    envelopeSlider[2].setRange(-60, 0, 0.1);
    
    for(int i = 0; i < 4; i++) {
        addAndMakeVisible(oscControls[i]);
        oscControls[i].setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
        oscControls[i].setTextBoxStyle(Slider::TextBoxBelow, false, oscControls[i].getTextBoxWidth(), oscControls[i].getTextBoxHeight());
    }
    
    addAndMakeVisible(pitchLabel);
    pitchLabel.setText("Coarse Tune", NotificationType::dontSendNotification);
//    pitchLabel.attachToComponent(&oscControls[0], false);
    
    addAndMakeVisible(volumeLabel);
    volumeLabel.setText("Level", NotificationType::dontSendNotification);
    volumeLabel.attachToComponent(&oscControls[1], false);
    
    oscControls[0].setRange(-24, 24, 1); // Pitch
    oscControls[0].setValue(0);
    oscControls[0].setDoubleClickReturnValue(true, 0);
    
    oscControls[1].setRange(-60, 0, 0.01); // Volume Control
    oscControls[1].setValue(-6);
    oscControls[1].setTextValueSuffix("dB");
    oscControls[1].setDoubleClickReturnValue(true, -6);
}

OscillatorComponent::~OscillatorComponent()
{
}

void OscillatorComponent::paint(Graphics& g)
{
    // Panel Outline
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
    
    // Panel Bar Left
    oscName.setText(labelName, dontSendNotification);
    oscName.setBounds(getWidth() / 20, getHeight() * 0.05, getWidth() / 3, getHeight() / 5);
    g.fillRoundedRectangle(0, 0, getWidth() * 0.5, getHeight() / 3.5, 5);
    
    // WaveTable
//    g.drawRoundedRectangle(getWidth() / 3, 0, getWidth() / 3, getHeight(), 5, 5);
//    waveTypeBox.setBounds(getWidth() / 3, 0, getWidth() / 3, getHeight() / 5);
        
    // Panel Bar Right
    g.fillRoundedRectangle(getWidth() * 0.5, 0, getWidth() * 0.5, getHeight() / 3.5, 5);
    
    // Oscillator Controls
    g.drawRect(0, 0, getWidth() * 0.5, getHeight());
    oscControls[0].setBounds(getWidth() / 20, getHeight() / 2.5, getWidth() / 6, getHeight() / 1.75);
    pitchLabel.setBounds(20, getHeight() / 3.25, oscControls[0].getTextBoxWidth(), oscControls[0].getTextBoxHeight());
    
    oscControls[1].setBounds(getWidth() / 4, getHeight() / 2.5, getWidth() / 6, getHeight() / 1.75);
    volumeLabel.setBounds(getWidth() / 6 + 50, getHeight() / 3.25, oscControls[1].getTextBoxWidth(), oscControls[1].getTextBoxHeight());
    
    // Envelope Outline
    for(int i = 0; i < 4; i++)
        envelopeSlider[i].setBounds((i * 35) + (getWidth() * 0.6), getHeight() / 3.3, getWidth() / 12, getHeight() / 1.5);
    g.drawRect(getWidth() * 0.5, 0, getWidth() * 0.5, getHeight());
    
    // Power Button
//    powerButton.setBounds(getWidth() * 0.01, getHeight() * 0.05, getWidth() / 26, getHeight() / 6);
}


void OscillatorComponent::setLabelText(std::string labelText)
{
    labelName = labelText;
}

bool OscillatorComponent::isOscillatorOn()
{
    return powerButton.isButtonOn();
}
