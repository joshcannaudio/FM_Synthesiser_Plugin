/*
  ==============================================================================

    MyComponent.h
    Created: 4 Sep 2022 4:11:45pm
    Author:  Joshua Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MyComponent : public Component {
public:
    /** Constructor */
    MyComponent();
    
    /** Destructor */
    ~MyComponent();
    
    /** Triggers when mouse enters component */
    void mouseEnter(const MouseEvent &event) override;
    
    /** Triggers when mouse leaves component */
    void mouseExit(const MouseEvent &event) override;
    
    /** Triggers when mouse button is down inside component */
    void mouseDown(const MouseEvent &event) override;
    
    /** Triggers when mouse button is up inside component */
    void mouseUp(const MouseEvent &event) override;

    /** Returns true when mouse is inside component */
    const bool isOnComponent();
    
    /** Returns true when mouse button is clicked inside component */
    const bool buttonIsDown();
    
    /** If component is a button this will return true if the button is engaged */
    const bool isButtonOn();
    
    /** Called when mouse event is triggered */
    virtual void mouseUpdate();
        
private:
    bool onComponent = false;
    bool buttonDown = false;
    bool buttonIsOn = false;
};
