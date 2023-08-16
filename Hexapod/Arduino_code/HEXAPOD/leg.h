#ifndef LEG_H
#define LEG_H

#include <Servo.h>

class Math;

class Leg{
public:
  Leg(unsigned int pin_no1,unsigned int pin_no2,unsigned int pin_no3,Math* calculator);
  int length_thigh;
  int length_calf;
private:
  Math* calculator;
  Servo servo_thigh1;
  Servo servo_thigh2;
  Servo servo_knee;

  float speed;

  unsigned int pin_thigh1;
  unsigned int pin_thigh2;
  unsigned int pin_knee;

  double angle_thigh1;
  double angle_thigh2;
  double angle_knee;

  double prev_angle_thigh1;
  double prev_angle_thigh2;
  double prev_angle_knee;

  double error_angle_thigh1;
  double error_angle_thigh2;
  double error_angle_knee;

  unsigned long time_elapsed;


private:

public:
  void Update(unsigned long time);
  float GetSpeed();
  void SetAngles(double thigh1,double thigh2,double knee);
  void Reset();

};

#endif