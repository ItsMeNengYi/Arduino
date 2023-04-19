#include <Arduino.h>
#include <SoftwareSerial.h> 

#include "Display.h"
#include "Ultrasound.h"

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
Display MyDisplay("HEY");
Sensor mySensor(11,12,&MyDisplay);
void setup() {
  // Serial.begin(9600);
}

void loop() {
  // Serial.println(mySensor.get_distance());
  MyDisplay.Update_display();
}