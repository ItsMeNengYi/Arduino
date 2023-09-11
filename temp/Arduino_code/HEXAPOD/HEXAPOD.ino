#include <Arduino.h>
#include <ESP32Servo.h>

#include "hexapod.h"
#include "leg.h"
#include "math.h"

Math calculator;
// Leg demoleg(10,11,12,&calculator);
Leg demoleg(2,4,5,&calculator);

void setup() {
  // Serial.begin(9600);
  demoleg.Reset();
  delay(500);
}

void loop() {
  
  demoleg.Reset();
  // demoleg.Update(millis());

}
