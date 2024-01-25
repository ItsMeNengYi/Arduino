#include "controller.h"
#include "hexapod.h"

#define VRX_PIN A0 // Arduino pin connected to VRX pin
#define VRY_PIN A1 // Arduino pin connected to VRY pin
#define  SW_PIN 2

Controller::Controller(Hexapod* hexapod) 
  : button(SW_PIN){
  this->button.setDebounceTime(50);// set debounce time to 50 milliseconds
  this->hexapod = hexapod;
}

void Controller::Update(){
  button.loop();
  
  xVal = analogRead(VRX_PIN);
  yVal = analogRead(VRY_PIN);
  // xNormVal = (double)xVal/(double)xMaxVal*2-1;
  // yNormVal = (double)yVal/(double)yMaxVal*2-1;
  xNormVal = round(((double)xVal/(double)xMaxVal*2-1)* 10)/10.0;
  yNormVal = round(((double)yVal/(double)yMaxVal*2-1)* 10)/10.0;
  hexapod->SetXYPos(xNormVal, yNormVal);

  bValue = button.getState();

  if (button.isPressed()) {
    hexapod->SetButtonState(1);
  }

  if (button.isReleased()) {
    hexapod->SetButtonState(0);
  }
}