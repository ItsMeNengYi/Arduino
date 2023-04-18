#ifndef PROJECT_H
#define PROJECT_H

#include <Arduino.h>
#include "alphabet.h"

class Display {
  /*
    connect pin 1 to 10
  */
public:
  Display(String text);

private:
  unsigned long startTime;
  unsigned int interval;
  int frame_no;
  String text;
  int length;
  bool** wordArray;

public:
  void Update_display();

public:
  //Setter
  void set_text_and_length(String value);
  void set_interval(unsigned int value);
  //Getter
  int get_frame_no();

private:
  bool** stringToArray();
  bool** addWords(bool*** matrix_array);
  bool** CreateArray(int rows, int cols);
  void copyArray(bool **array1, bool** array2);
  void display(bool** matrix);
  void AllLow();
  void High(int num);
  void Low(int num);
};

#endif