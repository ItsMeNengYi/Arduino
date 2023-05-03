#include <Arduino.h>

#include "Display.h"
#include "Ultrasound.h"
#include "Bluetooth.h"

Display MyDisplay(" ");
BluetoothModule MyBlue(12,13);
Sensor MySensor(15,14,&MyDisplay,&MyBlue);
void setup() {
  // MySensor.set_function_range();
}

void loop() {
  MyBlue.Update();
  // MySensor.Update();
  MyDisplay.Update_display();
}