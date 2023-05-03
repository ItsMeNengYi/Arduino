#include "Ultrasound.h"

Sensor::Sensor(int echo,int trig,Display* display,BluetoothModule* blue) {
  this->echoPin = echo;
  this->trigPin = trig;
  this->isHolding = false;
  this->current_track = "None";
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  this->MyDisplay = display;
  this->MyBlue = blue;
  MyBlue->SetSensor(this);
}

void Sensor::Update(){
  // MyDisplay->set_text(current_track);
  if(In_range()){
    // MyDisplay->set_text("Yes?");
    // startTime = millis();
    // prevdistance = get_distance();
    // get_run_command();
    return;
  }
  
  return;
}
bool Sensor::In_range() {
  get_distance();
  if ((distance>function_range.start)&&(distance<function_range.end)){
    return true;
  }
  return false;
}

/*
  'O' = default, none
  'N' = next track
  'P' = prev track
  'S' = pause track
  'V' = set volume
  'U' = volume up
  'D' = volume down
*/

void Sensor::get_run_command() {
  while(1){
      unsigned long currentTime = millis(); 
      unsigned long elapsedTime = currentTime - startTime; 
      MyDisplay->Update_display();
      // Waiting for too long
      if(elapsedTime>3000){
        break;
      }

      // // Setting Volume
      // if(!In_range()){
      //   isHolding = false;
      // }
      // if(isHolding&&(elapsedTime>=2000)){
      //   display_text("Vol");
      //     while(In_range()){
      //       MyDisplay->Update_display();
      //     }
      //   break;
      // }

      // // Next Track
      // if(get_distance()>prevdistance+2){
      //   MyBlue->NextTrack();
      //   display_text("Next");
      //   break;
      // }

      // // Previous Track
      // if (get_distance()<prevdistance-2){
      //   MyBlue->PrevTrack();
      //   display_text("Prev");
      //   break;
      // }
    
  }
}

void Sensor::set_current_track(String track){
  current_track = track;
  MyDisplay->set_text(current_track);
}

void Sensor::set_function_range() {
  prevdistance = get_distance();
  display_text("L?");
  MyDisplay->set_text("?");
  while(get_distance()>prevdistance-2){  
    MyDisplay->Update_display();
  }
  display_text((String)(int)distance);
  function_range.start = (int)distance;
  display_text("R?");
  MyDisplay->set_text("?");
  while(get_distance()>prevdistance-2){  
    MyDisplay->Update_display();
  }
  display_text((String)(int)distance);
  function_range.end = (int)distance;
  return;
}

float Sensor::get_distance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}
void Sensor::display_text(String text){
  MyDisplay->set_text(text);
  while(true){
    if(MyDisplay->is_last_frame()){
      break;
    }
    MyDisplay->Update_display();
  }
  return;
}