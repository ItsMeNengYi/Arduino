/*servo motor driver board control
   Home Page
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver srituhobby = Adafruit_PWMServoDriver();

#define servoMIN 544
#define servoMAX 2400

void setup() {
  Serial.begin(9600);
  srituhobby.begin();
  srituhobby.setPWMFreq(60);
}

void loop() {
  for (int servo = 0; servo < 3; servo++ ) {
    srituhobby.setPWM(servo, 0, servoMIN);
    Serial.println(servo);
    delay(300);
  }

}