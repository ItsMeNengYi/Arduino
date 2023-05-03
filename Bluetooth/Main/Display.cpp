#include "Display.h"

Display::Display(String text){
  this->text = text;
  this->interval = 150;
  this->frame_no = 1;
  this->startTime = millis();
  this->length = text.length();
  this->last_frame = (length * 6)-5;
  this->wordArray = stringToArray();
  for(int x=1;x<=10;x++){
    pinMode(x, OUTPUT);
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

void Display::set_interval(unsigned int value){
  interval = value;
}

void Display::Update_display(){
  unsigned long currentTime = millis(); 
  unsigned long elapsedTime = currentTime - startTime; 
  if (elapsedTime>= interval) {
    startTime = millis();
    frame_no++;
  }
  if(frame_no>last_frame||length==1){
    frame_no = 1;
  }
  display(wordArray);
}


bool** Display::stringToArray(){
  int ascii_no = 0;
  bool*** array = new bool**[length];
  
  for(int index=0; index<length; index++){
    ascii_no = (int)text[index]-32;
    array[index] =  CreateArray(5, 5);

    bool** alphabet = CreateArray(5, 5);
    for (int i=0; i<5; i++) {
      for (int j=0; j<5; j++) {
        alphabet[i][j]= Alphabet[ascii_no][i][j];
      }
    }

    copyArray(array[index], alphabet);
  }


  bool** arr = addWords(array);
  return arr;
}

bool** Display::addWords(bool*** matrix_array) {
 int row,column,spacing = 1;
 bool** final = CreateArray(5, (5+spacing)*length);
  for (int letter=0; letter<length; letter++){
    row = 5;
    column = 5;
    for (int i=0;i<row;i++){
      for (int j=0;j<column;j++){
        final[i][j+ letter*(5 + spacing)] = matrix_array[letter][i][j];
      }
    }
  }
  return final;
}

void Display::display(bool** matrix) {
  for(int x=0; x<5; x++){
    AllLow();
    for(int y=0; y<5; y++){
      if (matrix[x][y+frame_no-1]){
        High(x+1);
        Low(y+6);
      }
      else{
        High(y+6);
      }
    }
    delay(3);
  }
}

void Display::copyArray(bool **array1, bool** array2) {
  for (int i=0; i<5; i++) {
      for (int j=0; j<5; j++) {
        array1[i][j] = array2[i][j];
      }
  }
}

bool** Display::CreateArray(int rows, int cols){
  bool** array = new bool*[rows];
  for (int i=0; i<rows; i++) {
    array[i] = new bool[cols];
    for (int j=0; j<cols; j++) {
      array[i][j] = 0;      
    }
  }
  return array;
}

void Display::AllLow(){
  for(int x=1;x<=10;x++){
    Low(x);
  }
}

void Display::High(int num) {
  digitalWrite(num,HIGH);
}

void Display::Low(int num) {
  digitalWrite(num,LOW);
}