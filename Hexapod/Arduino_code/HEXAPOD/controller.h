#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <ezButton.h>

class Hexapod;
class Controller{
public:
  Controller(Hexapod* hexapod);

private:
  ezButton button;
  Hexapod* hexapod;
  double xVal = 0; // To store value of the X axis
  double yVal = 0; // To store value of the Y axis
  double xMaxVal = 710;
  double yMaxVal = 710;
  double xNormVal = 0;
  double yNormVal = 0;
  int bValue = 0; // To store value of the button

public:
  void Update();
};

#endif
