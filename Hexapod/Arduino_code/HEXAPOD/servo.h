#ifndef SERVO_H
#define SERVO_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define servoMIN 544
#define servoMAX 2400

class MyServo{
public:
  MyServo();
private:
  Adafruit_PWMServoDriver servoDriver1;
  Adafruit_PWMServoDriver servoDriver2;
  short DS3218servoMin = 544;
  short DS3218servoMax = 2400;
  
  short DS3235servoMin = 500;
  short DS3235servoMax = 2500;
  
  double pulseWidth;
  double curMin;
  double curMax;
  short SType;
  short servotype[33] = {0,0,0,0,0,2,1,1,0,2,1,1,0,2,1,1,0,2,1,1,0,2,1,1,0,2,1,3,0,0,0,0,0};
public:
  void initiate();
  void SetAngle(unsigned short index,double angle);
};

#endif