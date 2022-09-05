/*
  ==============================================================================

    EffectsRack.cpp
    Created: 4 Sep 2022 10:23:29pm
    Author:  Joshua Cann

  ==============================================================================
*/

#include "EffectsRack.h"

Effect::Effect()
{
    addAndMakeVisible(powerButton);
    addAndMakeVisible(label);
    for(int i = 0; i < 3; i++) {
        addAndMakeVisible(parameters[i]);
        parameters[i].setSliderStyle(Slider::RotaryVerticalDrag);
        parameters[i].setTextBoxStyle(Slider::TextBoxBelow, false, parameters[i].getTextBoxWidth() * 0.5, parameters[i].getTextBoxHeight() * 0.75);
//        sliderLabels[i].attachToComponent(&parameters[i], false);
        addAndMakeVisible(sliderLabels[i]);
    }
}

void Effect::paint(Graphics& g)
{
    // Set Label
    label.setText(labelText, NotificationType::dontSendNotification);
    
    // Panel
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight() * 0.25, 5);
    
    // Individual Outline
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
    
    // Power Button
    powerButton.setBounds(4, 4, getWidth() / 14, getHeight() / 7);
    
    // Label
    label.setBounds(powerButton.getRight() * 1.5, 0, getWidth() / 2, getHeight() / 4);
    
    parameters[0].setBounds(0, getHeight() / 3.5, getWidth() / 3, getHeight() * 0.65);
    sliderLabels[0].setBounds(0, getHeight() / 3.5, getWidth() / 8, getHeight() * 0.2);
    
    parameters[1].setBounds(getWidth() / 3, getHeight() / 3.5, getWidth() / 3, getHeight() * 0.65);
    sliderLabels[1].setBounds(getWidth() / 3, getHeight() / 3.5, getWidth() / 8, getHeight() * 0.2);
    
    if(isDistortion) {
        parameters[2].setBounds(getWidth() / 1.5, getHeight() / 3.5, getWidth() / 3, getHeight() * 0.65);
        sliderLabels[2].setBounds(getWidth() / 1.5, getHeight() / 3.5, getWidth() / 8, getHeight() * 0.2);
    }
}

EffectsRack::EffectsRack()
{
    for(int i = 0; i < 2; i++) {
        effect[i].labelText = effectLabels[i];
        addAndMakeVisible(effect[i]);
    }
    
    for(int i = 0; i < 3; i++) {
        std::string distortionSliderText[3] = { "Drive", "Shape", "Mix" };
        std::string modulatorSliderText[3] = { "Rate", "Depth", "Mix" };
        effect[0].sliderLabels[i].setText(distortionSliderText[i], NotificationType::dontSendNotification);
        effect[1].sliderLabels[i].setText(modulatorSliderText[i], NotificationType::dontSendNotification);
    }
    
    effect[0].isDistortion = true;
    effect[1].isDistortion = false;
    
    effect[0].parameters[0].setRange(0, 1, 0.01);
    effect[0].parameters[0].setValue(0.2);
    effect[0].parameters[1].setRange(0, 100, 1);
    effect[0].parameters[1].setTextValueSuffix("%");
    effect[0].parameters[1].setValue(80);
    effect[0].parameters[2].setRange(0, 100, 1);
    effect[0].parameters[2].setTextValueSuffix("%");
    effect[0].parameters[2].setValue(30);
    
    
    effect[1].parameters[0].setRange(0, 20, 0.1);
    effect[1].parameters[0].setValue(5);
    effect[1].parameters[0].setTextValueSuffix("Hz");
    effect[1].parameters[1].setRange(0, 100, 1);
    effect[1].parameters[1].setValue(20);
    effect[1].parameters[1].setTextValueSuffix("%");
}

void EffectsRack::paint(Graphics& g)
{
    // Overall Outline
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
    
    effect[0].setBounds(0, 0, getWidth(), getHeight() / 2);
    effect[1].setBounds(0, effect[0].getBottom(), getWidth(), getHeight() / 2);
}

bool EffectsRack::isEffectOn(int index)
{
    return effect[index].powerButton.isButtonOn();
}

