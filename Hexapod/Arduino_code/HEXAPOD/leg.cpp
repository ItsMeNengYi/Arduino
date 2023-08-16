
#include "leg.h"
#include "math.h"

Leg::Leg(unsigned int pin_no1,unsigned int pin_no2,unsigned int pin_no3,Math* calculator){
  this->speed = 1;
  this->length_thigh = 11;
  this->length_calf = 17;
  this->servo_thigh1.attach(pin_no1);
  this->servo_thigh2.attach(pin_no2);
  this->servo_knee.attach(pin_no3);
  this->calculator = calculator;
  this->prev_angle_thigh1 = 0;
  this->prev_angle_thigh2 = 0;
  this->prev_angle_knee = 0;
  error_angle_thigh1 = 90 - servo_thigh1.read();
  error_angle_thigh2 = 90 - servo_thigh2.read();
  error_angle_knee = 120 - servo_knee.read();
}


void Leg::Update(unsigned long time){
  calculator->CalculateAngle(this,time);
  calculator->GetAngle(this);

  //transform
  angle_thigh1+=135;
  angle_thigh2+=135;
  // error
  angle_thigh1+=error_angle_thigh1;
  angle_thigh2+=error_angle_thigh2;
  angle_knee+=error_angle_knee;
  
  Serial.print(angle_thigh1);
  Serial.print(" ");
  Serial.print(angle_thigh2);
  Serial.print(" ");
  Serial.println(angle_knee);

  servo_thigh1.write(angle_thigh1/270*180); 
  prev_angle_thigh1 = angle_thigh1;

  servo_thigh2.write((angle_thigh2/270)*180); 
  prev_angle_thigh2 = angle_thigh2;

  servo_knee.write(angle_knee/270*180); 
  prev_angle_knee = angle_knee;
}

void Leg::SetAngles(double thigh1,double thigh2,double knee){
  angle_thigh1 = thigh1;
  angle_thigh2 = thigh2;
  angle_knee = knee;
}

void Leg::Reset(){
  servo_thigh1.write(90); 
  servo_thigh2.write(90); 
  servo_thigh1.write(120); 
}

float Leg::GetSpeed(){
  return speed;
}
