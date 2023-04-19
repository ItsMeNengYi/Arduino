#include <Arduino.h>
#include <SoftwareSerial.h> 
#include "Display.h"


// SoftwareSerial MyBlue(10, 9); // RX | TX 
// void setup() 
// {   
//   Serial.begin(9600);
//   MyBlue.begin(9600); 
// } 
// void loop() 
// { 
//   if(MyBlue.available() > 0) 
//   {
//     char receive = MyBlue.read(); //Read from Serial Communication
//     Serial.print(receive);
//     MyBlue.write("Y");
//   }
  
// } 

Display MyDisplay("H");

void setup() {
}; 


void loop() {
  MyDisplay.Update_display();
}