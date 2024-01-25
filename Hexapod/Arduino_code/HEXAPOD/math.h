#ifndef MATH_H
#define MATH_H

#include <Arduino.h>
#include "leg.h"

class Math{
public:
  Math();

private:
  double speed;

  double thigh_length;
  double calf_length;

  double r_x;
  double r_y;
  double r_z;
  double temp_x;
  double temp_y;
  double temp_z;

  double sita1;
  double sita2;
  double phi;

  double r_matrix[2][2] = {{0,0},{0,0}};
  double temp_matrix[4][4]= {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
private:
  void formula_HalfCircle();

public:
  void Coord_Rotate(double *x,double *y,double *z,double pitch, double yaw, double roll);
  void Rotation_Matrix(double angle);

public:
  // void CalculateAngle(Leg* leg, unsigned long time_elapsed);
  void CalculateAngle(double r_x, double r_y, double r_z);
  void GetAngle(Leg* leg);

  void SetSpeed(double spd);
  void SetLegLength(double thigh,double calf);

};

#endif