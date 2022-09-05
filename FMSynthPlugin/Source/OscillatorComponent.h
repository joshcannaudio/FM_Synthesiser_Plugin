/*
  ==============================================================================

    OscillatorComponent.h
    Created: 4 Sep 2022 4:11:09pm
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PowerButton.h"

class OscillatorComponent : public Component {
public:
    /** Constructor */
    OscillatorComponent();
    
    /** Destructor */
    ~OscillatorComponent();
    
    /** Draws the Component */
    void paint(Graphics& g) override;
    
    /** Sets oscillator name */
    void setLabelText(std::string labelText);
    
    /** */
    bool isOscillatorOn();
    
    Slider envelopeSlider[4];
    Slider oscControls[4];
    ComboBox waveTypeBox;
private:
    PowerButton powerButton;
    
    Label oscName;
    Label pitchLabel, volumeLabel;
    std::string labelName;
    
    
    Array<std::string> waves = { "Sine", "Sawtooth", "Triangle", "Square" };
};
