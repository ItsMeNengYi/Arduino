#include <Arduino.h>

#include "Display.h"
#include "Ultrasound.h"
#include "Bluetooth.h"

Display MyDisplay(" ");
BluetoothModule MyBlue(12,13,&MyDisplay);
Sensor MySensor(9,8,&MyDisplay,&MyBlue);
String currentTrack;
void setup() {
  // Serial.begin(9600);
  MySensor.set_function_range();
}

void loop() {
  currentTrack = MyBlue.Update();
  if(currentTrack!=""){
    MyDisplay.set_text(currentTrack,1);
  }
  MySensor.Update();
  MyDisplay.Update_display();
}