#ifndef LEG_H
#define LEG_H

#include "servo.h"
#include "legIndex.h"

class Math;
class Leg{
public:
  Leg(Math* calculator, MyServo* driver);
  double length_thigh;
  double length_calf;
private:
  Math* calculator;
  MyServo* driver;

  float speed;

  Index index;

  double angle_hip;
  double angle_thigh;
  double angle_knee;

  double prev_angle_hip;
  double prev_angle_thigh;
  double prev_angle_knee;

  unsigned long time_elapsed;

private:

public:
  // void Update(unsigned long time);
  void Update();
  void Reset();
  void TurnAll(double hip,double thigh,double knee);
  void TurnHip(double degree);
  void TurnThigh(double degree);
  void TurnKnee(double degree);

  void GoToPosition(double x, double y, double z);

public:
  // Getter and Setter
  void SetIndex(double hip,double thigh,double knee);
  float GetSpeed();
  void SetAngles(double hip,double thigh,double knee);
};

#endif