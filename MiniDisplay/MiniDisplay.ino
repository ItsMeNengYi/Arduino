#include <Arduino.h>
#include "functions.h"
#include "alphabet.h"

/*
connect row led to pin 1~5
connect column led to pin 6~10
*/

#define Method5                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  

bool empty[5][5] = {
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0}
};


#ifdef Method1
  unsigned long startTime;
  unsigned int interval = 200;
  int frame_no = 1;
  String text = "KAINI";
  const short length = 5;
  bool** wordArray;
  
  void setup() {
    startTime = millis();
    for(int x=1;x<=10;x++){
      pinMode(x, OUTPUT);
    }
    wordArray= stringToArray(text);
  }; 
  

  void loop() {
    unsigned long currentTime = millis(); 
    unsigned long elapsedTime = currentTime - startTime; 
    if (elapsedTime>= interval) {
      startTime = millis();
      frame_no++;
    }
    if(frame_no>(length * 6)-5+1){
        frame_no = 1;
    }
    DisplayBitWise(wordArray,frame_no-1);
  }
#endif

#ifdef Method2
  unsigned long startTime;
  unsigned int interval = 200;
  int frame_no = 1;
  bool** wordArray; 
  String text= "GOODNIGHTWXYZYXWWXYZYXW";
  int length = text.length();
  int* ArrayOfindex = GetArrayOfIndex(text);
  void setup() {
    startTime = millis();
    for(int x=1;x<=10;x++){
      pinMode(x, OUTPUT);
    }
  }

  void loop() {
    unsigned long currentTime = millis(); 
    unsigned long elapsedTime = currentTime - startTime; 
    if(frame_no>length-1){
        frame_no = 1;
      }
    if(frame_no>=10&&frame_no<=22){
        interval = 100;
      }else{
      interval = 500;
    }
    if (elapsedTime>= interval) {
      startTime = millis();
      frame_no++;
    }
    DisplayBitWise(Alphabet[ArrayOfindex[frame_no-1]]);
  }
#endif

#ifdef Method3
  unsigned long startTime;
  unsigned int interval = 200;
  int frame_no = 1;
  String text = "ABCDEFG";
  const short length = 7;
  bool* lineArray;
  
  void setup() {
    startTime = millis();
    for(int x=1;x<=10;x++){
      pinMode(x, OUTPUT);
    }
    lineArray= stringToLineArray(text);
  }; 
  

  void loop() {
    unsigned long currentTime = millis(); 
    unsigned long elapsedTime = currentTime - startTime; 
    if (elapsedTime>= interval) {
      startTime = millis();
      frame_no++;
    }
    if(frame_no>(length * 6)-5+1){
        frame_no = 1;
    }
    DisplayBitWise(lineArray,frame_no-1,6);
  }
#endif

#ifdef Method4
//MEGA
  unsigned long startTime;
  unsigned int interval = 500;
  int frame_no = 1;
  String text = "KAINIGETOFFER";
  const short length = text.length();
  bool** wordArray;

  
  void setup() {
    startTime = millis();
    for(int x=1;x<=10;x++){
      pinMode(x, OUTPUT);
    }
    wordArray = stringToArray(text);
  }; 
  

  void loop() {
    unsigned long currentTime = millis(); 
    unsigned long elapsedTime = currentTime - startTime; 
    if (elapsedTime>= interval) {
      startTime = millis();
      frame_no++;
    }
    if(frame_no>(length * 6)-5+1){
      frame_no = 1;
    }
    Display(wordArray,frame_no-1);
  }
#endif

#ifdef Method5
  //Bluetooth display
  unsigned long startTime;
  unsigned int interval = 200;
  int frame_no = 1;
  String text = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int length;
  bool** wordArray;

  
  void setup() {
    display_setup();
    wordArray = display_set_word(text,startTime,length);
  }; 
  

  void loop() {
    Update(wordArray,length,frame_no,startTime,interval);
  }
#endif