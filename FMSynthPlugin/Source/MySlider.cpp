/*
  ==============================================================================

    MySlider.cpp
    Created: 3 Sep 2022 10:11:56am
    Author:  Joshua Cann

  ==============================================================================
*/

#include "MySlider.h"

MySlider::MySlider()
{
    addAndMakeVisible(slider);
}

MySlider::~MySlider()
{
    
}

void MySlider::createSlider(String SliderID, AudioProcessorValueTreeState& apvts)
{
    slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(Slider::TextBoxBelow, true, slider.getTextBoxWidth(), slider.getTextBoxHeight());
    addAndMakeVisible(slider);
    
    sliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(apvts, SliderID, slider);
}

void MySlider::paint(Graphics& g)
{
    slider.setBounds(getLocalBounds());
    
}
