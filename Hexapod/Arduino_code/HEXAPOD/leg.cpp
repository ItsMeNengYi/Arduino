#include "leg.h"
#include "math.h"

Leg::Leg(Math* calculator,MyServo* driver){
  this->speed = 1;
  this->length_thigh = 110;
  this->length_calf = 170;
  this->prev_angle_hip = 0;
  this->prev_angle_thigh = 0;
  this->prev_angle_knee = 0;
  this->calculator = calculator;
  this->driver = driver;
}
void Leg::Update(){
  // //transform
  // angle_hip+=135;
  // angle_thigh+=135;
  // angle_knee = 270 - angle_knee;

  driver->SetAngle(index.hip,angle_hip);
  prev_angle_hip = angle_hip;

  driver->SetAngle(index.thigh,angle_thigh);
  prev_angle_thigh = angle_thigh;

  driver->SetAngle(index.knee,angle_knee);
  prev_angle_knee = angle_knee;
}

void Leg::GoToPosition(double x, double y, double z){
  calculator->CalculateAngle(x,y,z);
  calculator->GetAngle(this);
  TurnAll(angle_hip,angle_thigh,angle_knee);
}

void Leg::SetAngles(double hip,double thigh,double knee){
  angle_hip = hip;
  angle_thigh = thigh;
  angle_knee = knee;
}

void Leg::Reset(){
  driver->SetAngle(index.hip,135);
  driver->SetAngle(index.thigh,135);
  driver->SetAngle(index.knee,180);
}

float Leg::GetSpeed(){
  return speed;
}

void Leg::SetIndex(double hip,double thigh,double knee){
  index.hip = hip;
  index.thigh = thigh;
  index.knee = knee;
}

void Leg::TurnAll(double hip,double thigh,double knee){
  driver->SetAngle(index.hip,hip);
  prev_angle_hip = hip;

  driver->SetAngle(index.thigh,thigh);
  prev_angle_thigh = thigh;

  driver->SetAngle(index.knee,knee);
  prev_angle_knee = knee;
}

void Leg::TurnHip(double degree){
  angle_hip = degree;
  driver->SetAngle(index.hip,angle_hip);
  prev_angle_hip = angle_hip;
}

void Leg::TurnThigh(double degree){
  angle_thigh = degree;
  driver->SetAngle(index.thigh,angle_thigh);
  prev_angle_thigh = angle_thigh;
}

void Leg::TurnKnee(double degree){
  angle_knee = degree;
  driver->SetAngle(index.knee,angle_knee);
  prev_angle_knee = angle_knee;
}

// void Leg::Update(unsigned long time){
//   calculator->CalculateAngle(this,time);
//   calculator->GetAngle(this);

//   //transform
//   angle_hip+=135;
//   angle_thigh+=135;
//   angle_knee = 270 - angle_knee;

//   // Serial.print(angle_hip);
//   // Serial.print(" ");
//   // Serial.print(angle_thigh);
//   // Serial.print(" ");
//   // Serial.println(angle_knee);

//   driver->SetAngle(index.hip,angle_hip);
//   prev_angle_hip = angle_hip;

//   driver->SetAngle(index.thigh,angle_thigh);
//   prev_angle_thigh = angle_thigh;

//   driver->SetAngle(index.knee,angle_knee);
//   prev_angle_knee = angle_knee;
// }

