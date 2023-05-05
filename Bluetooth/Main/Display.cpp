#include "Display.h"
#define New

Display::Display(String text){
  this->text = text;
  this->length = text.length();
  this->spacing = 1;
  this->interval = 150;
  this->frame_no = 1;
  this->startTime = millis();
  this->last_frame = (length * 6)-5;
  this->wordArray = stringToArray();
  for(int x=1;x<=10;x++){
    pinMode(x+increment, OUTPUT);
  }
}

int Display::get_frame_no(){
  return frame_no;
}

int Display::get_last_frame(){
  return last_frame;
}

bool Display::is_last_frame(){
  if (frame_no>=last_frame){
    return true;
  }
  else{
    return false;
  }
}

void Display::set_text(String value){
  if(prev_text!=value){
    frame_no = 1;
    prev_text = text;
    text = value;
    length = value.length();
    last_frame = (length * 6)-5;
    wordArray = stringToArray();
  }
}

void Display::set_text(int volume){
  frame_no = 1;
  length = 1;
  last_frame = (length * 6)-5;
  for(int i=0; i<5; i++) {
    for(int j=0; j<5; j++) {
      wordArray[i][j]= Volume[volume][i][j];
    }
  }
}

void Display::set_text(String value,bool optimised){
  if(prev_text!=value){
    optimiser = true;
    frame_no = 1;
    prev_text = text;
    text = value;
    length = value.length();
    last_frame = (length * 6)-5;
    tempArray = stringToArray();
  }
}

void Display::set_interval(unsigned int value){
  interval = value;
}

void Display::Update_display(){
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime; 
  if (elapsedTime>= interval) {
    startTime = millis();
    frame_no++;
    if(optimiser){
      wordArray = tempArray;
      optimiser = false;
      return;
    }
  }
  if(frame_no>last_frame||length==1){
    frame_no = 1;
  }
  display(wordArray);
  return;
}

void Display::display(bool** matrix) {
  for(int x=0; x<5; x++){
    AllLow();
    for(int y=0; y<5; y++){
      if (matrix[x][y+frame_no-1]){
        digitalWrite(x+1+increment,HIGH);
        digitalWrite(y+6+increment,LOW);
      }
      else{
        digitalWrite(y+6+increment,HIGH);
      }
    }
    delay(3);
  }
}

void Display::AllLow(){
  for(int x=1;x<=10;x++){
    digitalWrite(x+increment,LOW);
  }
}

bool** Display::stringToArray(){
  int ascii_no = 0;
  int rows=5,cols = (5+spacing)*length;
  bool** final = new bool*[rows];
  for (int i=0; i<rows; i++) {
    final[i] = new bool[cols];
  }
  
  for(int index=0; index<length; index++){
    ascii_no = (int)text[index]-32;
    for(int i=0; i<5; i++) {
      for(int j=0; j<6; j++) {
        if(j==5){
          final[i][index*(5+spacing)+j]=0;
        }else{
        final[i][index*(5+spacing)+j] = Alphabet[ascii_no][i][j];
        }
      }
    }
  }
  return final;
}