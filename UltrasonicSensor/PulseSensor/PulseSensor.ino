#include "functions.h"
#include "animation.h"

/*
connect row led to pin 1~5
connect column led to pin 6~8,11~12
connect trigPin to 9
connect echoPin to 10
connect VCC to 5V
connect GND to GND
*/

int** wordArray;
int TempArray[5][5]= {
  {1,1,1,1,1},
  {1,1,1,1,1},
  {1,1,1,1,1},
  {1,1,1,1,1},
  {1,1,1,1,1}
};
String text= "WXYZ";
int length = text.length();
int* ArrayOfindex = GetArrayOfIndex(text);
int frame_no = 1;
unsigned long startTime;
unsigned int interval = 100;

const int trigPin = 14;
const int echoPin = 15;
// defines variables
float prevdistance = 0;
void setup() {
  Serial.begin(9600);
  //Led
  for(int x=1;x<=10;x++){
      pinMode(x, OUTPUT);
  }
  // Sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  unsigned long currentTime = millis(); 
  // unsigned long elapsedTime = currentTime - startTime; 

  //   if (elapsedTime>= interval && Pulse(&prevdistance,10,9)) {
      
  //     Display(Alphabet[ArrayOfindex[frame_no-1]]);
  //     startTime = millis();
  //   }
  // }
  if(frame_no>length-1){
        frame_no = 1;
      }
  if (Pulse(&prevdistance,echoPin,trigPin)||frame_no!=1) {
  // unsigned long currentTime = millis(); 
  unsigned long elapsedTime = currentTime - startTime; 
    
    if (elapsedTime>= interval) {
      startTime = millis();
      frame_no++;
    }
    Display(Alphabet[ArrayOfindex[frame_no-1]]);
  }
}