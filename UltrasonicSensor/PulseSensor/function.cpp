#include <Arduino.h>
#include "functions.h"

bool Pulse(float* prevdistance,int echoPin,int trigPin){
  float distance;
  long duration;
  float speed;
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  speed = (distance-*prevdistance)*100000 /(duration*1000);
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  // Serial.print(" prevdistance: ");
  // Serial.print(*prevdistance);
  // Serial.print(" Speed: ");
  // Serial.println(speed);
  *prevdistance = distance;
  if(speed>1.45){
    return true;
  }
  return false;
}
int* GetArrayOfIndex(String words){
  int ascii_no = 0;
  int words_no = words.length();
  int* array = new int[words_no];
  
  for(int index=0; index<words_no; index++){
    ascii_no = (int)words[index]-65;
    array[index] = ascii_no;
  }
  return array;
}

void Display(int matrix[5][5]) {
  for(int x=0; x<5; x++){
    AllLow();
    for(int y=0; y<5; y++){
      if (matrix[x][y]){
        High(x+1);
        Low(y+6);
      }
      else{
        High(y+6);
      }
    }
    delay(1);
  }
}

void High(int num) {
  digitalWrite(num,HIGH);
}

void Low(int num) {
  digitalWrite(num,LOW);
}

void AllLow(){
  for(int x=1;x<=10;x++){
    Low(x);
  }
}

