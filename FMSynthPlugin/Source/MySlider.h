/*
  ==============================================================================

    MySlider.h
    Created: 3 Sep 2022 10:11:56am
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MySlider : public Component {
public:
    MySlider();
    
    ~MySlider();
    
    void createSlider(String SliderID, AudioProcessorValueTreeState& apvts);
    
    void paint(Graphics& g) override;
    
private:
    Slider slider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;
};

