#include "servo.h"
#include "hexapod.h"

MyServo::MyServo(){
  this->servoDriver1 = Adafruit_PWMServoDriver(0x40);
  this->servoDriver2 = Adafruit_PWMServoDriver(0x41);
}

void MyServo::initiate(){
  servoDriver1.begin();
  servoDriver1.setPWMFreq(333);
  servoDriver2.begin();
  servoDriver2.setPWMFreq(333);
}

void MyServo::SetAngle(unsigned short index,double angle){
  if(angle < 0 || angle > 270){
    Serial.print("ERROR: index ");
    Serial.print(index);
    Serial.print(" exceed normal range:");
    Serial.println(angle);
    return;
  }
  SType = servotype[index];
  // if(index == 9){
  // Serial.println(SType);
  // }
  if(SType != 0){
    switch (SType){
      case 1:
        curMin = DS3218servoMin;
        curMax = DS3218servoMax;
        break;
      case 2:
        curMin = DS3235servoMin;
        curMax = DS3235servoMax;
        break;
      case 3:
        curMin = -200;
        curMax = 4200;
        break;
    }
    pulseWidth = angle / 270 * (curMax - curMin) + curMin;
    if (pulseWidth < curMin) {
      pulseWidth = curMin;
    }else if(pulseWidth > curMax) {
      pulseWidth = curMax;
    }

    if(index<=16){
      servoDriver1.setPWM(index-1, 0, (int)pulseWidth);
    }else{
      servoDriver2.setPWM(index-17, 0, (int)pulseWidth);
    }
  }
}