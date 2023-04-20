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
  Sensor(int echo,int trig,Display* display);
private:
  Display* MyDisplay;
  int echoPin;
  int trigPin;
  unsigned long startTime;
  long duration;
  float distance;
  float prevdistance;
  Range function_range;
  char command;
  bool isSetting;
  String current_track;

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
  void Update();
  bool Has_command();

public:
  // Getter
  float get_distance();
  char get_command();
  // Setter
  void set_function_range();

private:
  char deter_command();
  void display_text(String text);
  void display_command();

};

#endif