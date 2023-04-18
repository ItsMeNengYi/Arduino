#include <Arduino.h>
/*
  value of y when equal 0
  left:23
  right:01
  front:03
  back:12
*/
int Direction(short botLeft,short topLeft,short topRight,short botRight){
  short array[] = {botLeft,topLeft,topRight,botRight};
  short deter[4];
  for(int x = 0;x<4;x++){
    pinMode(array[x], OUTPUT);
    digitalWrite(array[x],HIGH);
    for(int y = 0; y<4; y++){
      if(y != x){
        pinMode(array[y], INPUT);
        deter[y] = digitalRead(array[y]);
      }
    }
    if(!(deter[0])&!(deter[1])){
      Serial.print("left");
      }
  }

}
