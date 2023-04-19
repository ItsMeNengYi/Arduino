#include "Ultrasound.h"

Sensor::Sensor(int echo,int trig,Display* display) {
  this->echoPin = echo;
  this->trigPin = trig;
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  calculate_distance();
  this->MyDisplay = display;
  this->set_function_distance();
}

bool Sensor::Has_command() {

}
float Sensor::get_distance() {
  calculate_distance();
  return distance;
}
char Sensor::get_command() {

}


void Sensor::set_function_distance() {
  MyDisplay->set_text("Set");


}

float Sensor::calculate_distance() {
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