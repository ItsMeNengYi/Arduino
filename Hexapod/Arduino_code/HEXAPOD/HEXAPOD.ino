#include <Arduino.h>
#include "hexapod.h"
// #include "servo.h"

// MyServo testingDriver;
Hexapod neng2;
void setup() {
  // testingDriver = MyServo();
  // testingDriver.initiate();
  // Serial.begin(9600);
  neng2.InitiateDriver();
}

void loop() {
  // testingDriver.SetAngle(9,90);
  neng2.Update(millis());
  // neng2.Update();
  // delay(1000);
  // neng2.Reset();

}