/*
  ==============================================================================

    PowerButton.cpp
    Created: 4 Sep 2022 4:11:54pm
    Author:  Joshua Cann

  ==============================================================================
*/

#include "PowerButton.h"

void PowerButton::paint(Graphics& g)
{
    buttonIsOn = isButtonOn();
    buttonIsOn == true ? g.setColour(Colours::mediumpurple) : g.setColour(Colours::darkgrey);
    
    if(isOnComponent()) {
        if(buttonIsOn) {
            g.setColour(Colours::rebeccapurple);
        }
        if(!buttonIsOn) {
            g.setColour(Colours::darkslategrey);
        }
    }
    
    if(buttonIsDown()) {
        if(buttonIsOn) {
            g.setColour(Colours::grey);
        }
        if(!buttonIsOn) {
            g.setColour(Colours::purple);
        }
    }
    
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 10000);
    

}

void PowerButton::mouseUpdate()
{
    repaint();
}

bool PowerButton::isOn()
{
    return buttonIsOn;
}
