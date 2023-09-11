#include "servo.h"

MyServo::MyServo(){
  this->servoDriver = Adafruit_PWMServoDriver();
}

void MyServo::initiate(){
  servoDriver.begin();
  servoDriver.setPWMFreq(60);
}

void MyServo::SetAngle(unsigned short index,unsigned short angle){
  if(index >= 0 && index <= 15){
    unsigned short pulseWidth = angle / 270 * (2400 - 544) + 544;
    if (pulseWidth < 544) {
      pulseWidth = 544;
    }else if(pulseWidth > 2400) {
      pulseWidth = 2400;
    }
    servoDriver.setPWM(index, 0, pulseWidth);
  }
  return;
}