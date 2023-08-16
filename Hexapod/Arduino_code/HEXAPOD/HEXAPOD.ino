#include <Arduino.h>
#include <Servo.h>

#include "hexapod.h"
#include "leg.h"
#include "math.h"

Math calculator;
Leg demoleg(10,11,12,&calculator);

void setup() {
  // Serial.begin(9600);
  demoleg.Reset();
  delay(500);
}

void loop() {
  
  demoleg.Update(millis());
  delay(50);

}
