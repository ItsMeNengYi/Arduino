#include <Arduino.h>

#include "Display.h"
#include "Ultrasound.h"
#include "Bluetooth.h"

// Display MyDisplay(" ");
// Sensor MySensor(11,12,&MyDisplay);
BluetoothModule MyBlue(15,14);
void setup() {
  Serial.begin(9600);
}

void loop() {
  MyBlue.Update();
  // MySensor.Update();
  // MyDisplay.Update_display();
}