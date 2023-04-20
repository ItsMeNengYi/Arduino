#include "Ultrasound.h"

Sensor::Sensor(int echo,int trig,Display* display) {
  this->echoPin = echo;
  this->trigPin = trig;
  this->command = "O";
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  get_distance();
  this->MyDisplay = display;
  this->isSetting = true;
}

void Sensor::Update(){
  
  if(isSetting){
    set_function_range();
  }
  else if(Has_command()){
    MyDisplay->set_text("YES?");
    MyDisplay->Update_display();
    startTime = millis();
    get_command();
    display_command();
  }


}
bool Sensor::Has_command() {
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

char Sensor::deter_command(){
  get_distance();
  if (distance<function_range.start){
    return 'P';
  }
  if(distance>function_range.end){
    return 'N';
  }
}

void Sensor::display_command(){
  switch(command) {
    case 'N':
      display_text("Next Track");
      break;
    case 'P':
      display_text("Prev Track");
      break;
    default:
      break;
  }
}

char Sensor::get_command() {
  float temp;
  prevdistance = distance;
  while(1){
    unsigned long currentTime = millis(); 
    unsigned long elapsedTime = currentTime - startTime; 
    MyDisplay->Update_display();
    get_distance();
    if(elapsedTime>5000){
      break;
    }
    command = deter_command();
    if(command!="O"){
      return command;
    }
  }
  return "O";
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