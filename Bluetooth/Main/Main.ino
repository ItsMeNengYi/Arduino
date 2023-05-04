#include <Arduino.h>

#include "Display.h"
#include "Ultrasound.h"
#include "Bluetooth.h"

Display MyDisplay(" ");
BluetoothModule MyBlue(12,13,&MyDisplay);
Sensor MySensor(9,8,&MyDisplay,&MyBlue);
void setup() {
  Serial.begin(9600);
  MySensor.set_function_range();
}

void loop() {
  MyBlue.Update();
  MySensor.Update();
  MyDisplay.Update_display();
}