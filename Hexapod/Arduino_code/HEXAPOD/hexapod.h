#ifndef HEXAPOD_H
#define HEXAPOD_H

#include "legIndex.h"
#include "leg.h"
#include "math.h"
#include "servo.h"
#include "controller.h"

class Hexapod{
public:
  Hexapod();
  int radius;
private:
  Math calculator;
  MyServo driver;
  Controller joystick;
  Leg left_front;
  Leg left_mid;
  Leg left_back;
  Leg right_front;
  Leg right_mid;
  Leg right_back;

  String State;/* StandingUp Idle Walk Default */
  
  // For calculate desire position
  int period;
  double r_x;
  double r_y;
  double r_z;
  double r_x_2;
  double r_y_2;
  double r_z_2;
  double temp_x;
  double temp_y;
  double temp_z;
  double z_offset;
  double x_offset;
  double y_offset;
  double phase_angle;
  unsigned long start_time;
  double time_elapsed;

  // For control
  double X_pos_joystick; // -1 ~ 1
  double Y_pos_joystick; // -1 ~ 1
  bool button_state;
  
public: // movement
  void Walk(unsigned long time);
  void Stand(unsigned long time);
  void Update(unsigned long time);
  void Reset();
public: // Construct
  void InitiateDriver();
public: // Control
  void SetXYPos(double X, double Y);
  void SetButtonState(bool state);
};
#endif