/*
  ==============================================================================

    PowerButton.h
    Created: 4 Sep 2022 4:11:54pm
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MyComponent.h"

class PowerButton : public MyComponent {
public:
    /** Paints the button */
    void paint(Graphics& g) override;
    
    /** Updates when mouse event is triggered */
    void mouseUpdate() override;
    
    /** Returns true if button is engaged otherwise will return false */
    bool isOn();
    
private:
    bool buttonIsOn = false;
};
