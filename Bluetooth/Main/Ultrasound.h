#ifndef ULTRASOUND_H
#define ULTRASOUND_H

#include <Arduino.h>
#include "Display.h"
#include "Bluetooth.h"


struct Range {
  int start;
  int end;
};

class Sensor {
public:
  Sensor(int echo,int trig,Display* display,BluetoothModule* blue);
private:
  Display* MyDisplay;
  BluetoothModule* MyBlue;
  int echoPin;
  int trigPin;
  unsigned long startTime;
  unsigned long currentTime;
  unsigned long elapsedTime;
  long duration;
  float distance;
  float prevdistance;
  Range function_range;
  bool isHolding;
  bool getCommand;
  short right=0;
  short left=0;
  short middle=0;
  bool cooldown;
  int maxdistance=50;
  bool settingVolume = false;
  short zeroCount=0;
  int speed;
  int volume=13;

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
  bool In_range();

public:
  // Getter
  float get_distance();
  void get_run_command();
  // Setter
  void set_function_range();

private:
  void display_text(String text);
  void reset();

};

#endif