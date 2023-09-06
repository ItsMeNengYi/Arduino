#include <Adafruit_PWMServoDriver.h>

#include <Wire.h>

Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();

#define servoMIN 150
#define servoMAX 600

void setup() {
  Serial.begin(9600);
  driver.begin();
  driver.setPWMFreq(60);
}

void loop() {

  for (int servo = 3; servo >= 0; servo-- ) {
    driver.setPWM(servo, 0, servoMAX);
    Serial.println(servo);
    delay(300);
  }
}
