#include <Arduino.h>
#include "functions.h"

const short bLeft=7,bRight=6,tLeft=5,tRight=4;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  Direction(bLeft,tLeft,tRight,bRight);

}
