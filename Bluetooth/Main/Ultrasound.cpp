#include "Ultrasound.h"

Sensor::Sensor(int echo,int trig,Display* display,BluetoothModule* blue) {
  this->echoPin = echo;
  this->trigPin = trig;
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  get_distance();
  this->MyDisplay = display;
  this->MyBlue = blue;
  this->isSetting = true;
  this->isHolding = false;
  this->current_track = "None";
}

void Sensor::Update(){
  
  if(isSetting){
    set_function_range();
    Serial.println(function_range.start);
    Serial.println(function_range.end);
    isSetting = false;
  }
  else if(In_range()){
    MyDisplay->set_text("YES?");
    MyDisplay->Update_display();
    startTime = millis();
    get_run_command();
    MyDisplay->set_text(current_track);
  }


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
    get_distance();
    MyDisplay->Update_display();

    // Waiting for too long
    if(elapsedTime>5000){
      return;
    }

    // Setting Volume
    if(!In_range()){
      isHolding = false;
    }
    if(isHolding&&(elapsedTime>=2000)){
      display_text("Vol");
        while(In_range()){
          MyDisplay->Update_display();
        }
      return;
    }

    // Next Track
    if(get_distance()>function_range.end){
      MyBlue->NextTrack();
      display_text("Next");
      return;
    }

    // Previous Track
    if (get_distance()<function_range.start){
      MyBlue->PrevTrack();
      display_text("Prev");
      return;
    }
  
  }
  return;
}


void Sensor::set_function_range() {
  prevdistance = get_distance();
  display_text("L?");
  MyDisplay->set_text("?");
  while(get_distance()>prevdistance-3){  
    MyDisplay->Update_display();
  }
  display_text((String)(int)distance);
  function_range.start = (int)distance;
  display_text("R?");
  MyDisplay->set_text("?");
  while(get_distance()>prevdistance-3){  
    MyDisplay->Update_display();
  }
  display_text((String)(int)distance);
  function_range.end = (int)distance;
  MyDisplay->set_text("Done");
  isSetting = false;
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
  while(true){
      MyDisplay->set_text(text);
      if(MyDisplay->is_last_frame()){
        break;
      }
      
      MyDisplay->Update_display();
    }
}