#include "Ultrasound.h"

Sensor::Sensor(int echo,int trig,Display* display,BluetoothModule* blue) {
  this->echoPin = echo;
  this->trigPin = trig;
  this->isHolding = false;
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  this->MyDisplay = display;
  this->MyBlue = blue;
  MyBlue->SetSensor(this);
  this->cooldown = false;
}

void Sensor::Update(){
  if(settingVolume){
    if((millis()-startTime)>=250){
      if(zeroCount>4){
        settingVolume = false;
        cooldown = true;
        startTime = millis();
        reset();
        MyBlue->DoneSettingVol();
        return;
      }
      get_distance();
      speed = (distance-prevdistance)/0.25;
      if(speed==0){
        zeroCount++;
      }else if((abs(speed)<10)&&(abs(speed)>1)){
        zeroCount=0;
        if(speed<0&&volume>0){
          MyBlue->VolDown();
          volume--;
          // Serial.println("D");
        }else if(speed>0&&volume<25){
          MyBlue->VolUp();
          volume++;
          // Serial.println("U");
        }
        MyDisplay->set_text(volume);
      }
      startTime = millis();
      prevdistance = distance;
      return;
    }
    return;
  }
  currentTime = millis(); 
  if (((currentTime-startTime)>2000)&&cooldown){
    cooldown = false;
  }
  if(!cooldown){
    get_distance();
    if ((distance>function_range.start)&&(distance<function_range.end)){
      MyDisplay->set_text("?");
      startTime = millis();
      prevdistance = get_distance();
      reset();
      while(true){
        get_distance();
        currentTime = millis(); 
        elapsedTime = currentTime - startTime; 
        if(elapsedTime>10){
          if(((int)distance-(int)prevdistance)==0){
            middle++;
            // Serial.print("X");
          }else if ((distance-prevdistance)>0){
            right++;
            // Serial.print("R");
          }else{
            left++;
            // Serial.print("L");
          }
        }
        prevdistance=distance;
        // Waiting for too long
        if(elapsedTime>250){
          if((middle>=right)&&(middle>=left)){
            // Serial.println("Hold!");
            // Set Volume
            MyDisplay->set_text("VOL");
            prevdistance = get_distance();
            settingVolume = true;
            startTime = millis();
            return;
          }else if(right>left){
            MyBlue->NextTrack();
            MyDisplay->set_text("=>");
            // Serial.println("Right!");
            startTime = millis();
            cooldown = true;
            return;
          }else{
            MyBlue->PrevTrack();
            MyDisplay->set_text("<=");
            // Serial.println("Left!");
            startTime = millis();
            cooldown = true;
            return;
          }
          break;
        }
        if(elapsedTime>3000){
          break;
        }
        MyDisplay->Update_display();
      }
      startTime = millis();
      cooldown = true;
      return;
    }
  }
  return;
}

void Sensor::reset(){
  right=0;
  left=0;
  middle=0;
  zeroCount=0;
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


void Sensor::set_function_range() {
  prevdistance = get_distance();
  display_text("L?");
  MyDisplay->set_text("?");
  while(get_distance()>(int)prevdistance-2){  
    MyDisplay->Update_display();
  }
  display_text((String)(int)distance);
  function_range.start = (int)distance;
  display_text("R?");
  MyDisplay->set_text("?");
  while(get_distance()>(int)prevdistance-1){  
    MyDisplay->Update_display();
  }
  display_text((String)(int)distance);
  function_range.end = (int)distance;
  delay(10);
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
  if(distance>=maxdistance){
    distance = maxdistance;
  }
  return distance;
}

void Sensor::display_text(String text){
  MyDisplay->set_text(text);
  while(true){
    if(MyDisplay->is_last_frame()){
      return;
    }
    MyDisplay->Update_display();
  }
  return;
}