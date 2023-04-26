#include <Arduino.h>

#include "Display.h"
#include "Ultrasound.h"
#include "Bluetooth.h"

// Display MyDisplay(" ");
BluetoothModule MyBlue(15,14);
// Sensor MySensor(11,12,&MyDisplay,&MyBlue);
void setup() {
  Serial.begin(9600);
  // MySensor.set_function_range();
}

void loop() {
  MyBlue.Update();
  // MySensor.Update();
  // MyDisplay.Update_display();
}