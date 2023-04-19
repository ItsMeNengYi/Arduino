#ifndef ULTRASOUND_H
#define ULTRASOUND_H

#include <Arduino.h>
#include "Display.h"

struct Range {
  int start;
  int end;
};

class Sensor {
public:
  Sensor(int echo,int trig);
private:
  int echoPin;
  int trigPin;
  long duration;
  float distance;
  float prevdistance;
  Range init_distance_range;
  Range function_distance_range;
  char command;
  /*
    "O" = default, none
    "N" = next track
    "P" = prev track
    "S" = pause track
    "V" = set volume
    "U" = volume up
    "D" = volume down
  */

public:
  bool Has_command();

public:
  // Getter
  float get_distance();
  char get_command();
  // Setter
  void set_init_distance();
  void set_function_distance();
  void set_command(char comm);

private:
  float calculate_distance();
  char deter_command();

};

#endif