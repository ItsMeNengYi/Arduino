const byte servoPin = 9;
const uint8_t frequency = 333;//Hz
const long timeInterval = 10^6/frequency;//microsecond
const uint8_t deadBand = 3;//microsecond
#include<Servo.h>
#include "driver.h"
Servo servo1;
MyServo driver;
int prev_pos1 = 0;
int prev_pos2 = 0;
int prev_pos3 = 0;
int val_pin1 = A0;
int val_pin2 = A1;
int val_pin3 = A2;
float max = 1023;
void setup() {
  Serial.begin(9600);
  pinMode(val_pin1, INPUT);
  pinMode(val_pin2, INPUT);
  pinMode(val_pin3, INPUT);
  servo1.attach(servoPin);
}

void loop() {
  // myservo1.write(120); 
    // myservo2.write(90);  
  //   myservo3.write(90); 
  float val1 = analogRead(val_pin1);
  float temp1 = val1/max*270; 
  if((temp1 >= prev_pos1+1)||(temp1 <= prev_pos1-1)){
    servo1.write(temp1);
    driver.SetAngle(0,int(temp1));
  prev_pos1 = temp1;
  }

  float val2 = analogRead(val_pin2);
  float temp2 = val2/max*270; 
  if((temp2 >= prev_pos2+1)||(temp2 <= prev_pos2-1)){
    driver.SetAngle(1,int(temp2));
    prev_pos2 = temp2;
  }

  float val3 = analogRead(val_pin3);
  float temp3 = val3/max*270; 
  if((temp3 >= prev_pos3+1)||(temp3 <= prev_pos3-1)){
    driver.SetAngle(2,int(temp3));
    prev_pos3 = temp3;
  }
  Serial.println(temp1);
  // Serial.print(temp1/180*270);
  // Serial.print(" ");
  // Serial.print(temp2/180*270);
  // Serial.print(" ");
  // Serial.println(temp3/180*270);
  delay(10);
}