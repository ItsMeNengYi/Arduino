#include "Bluetooth.h"
#include "Ultrasound.h"

/*
    "O" = default, none
    "N" = next track
    "P" = prev track
    "S" = pause track
    "V" = set volume
    "U" = volume up
    "D" = volume down
  */


BluetoothModule::BluetoothModule(int RX,int TX,Display* display) : Blue(RX,TX){
  Blue.begin(9600);
  this->MyDisplay = display;
  this->CurrentTrack = "X";
  this->ReceivingTrack = false;
  this->word_counter = 0;
  this->word_length = 0;
}

String BluetoothModule::Update(){
  if(Blue.available() > 0) 
  {
    char receive = Blue.read(); //Read from Serial Communication
    if (receive == '['){
      *characters = "";
      ReceivingTrack = true;
      word_counter = 0;
      return "";
    }
    if (receive == ']'){
      char temp[word_counter];
      for(int x; x<word_counter;x++){
        temp[x]=characters[x];
      }
      CurrentTrack = String(temp);
      ReceivingTrack = false;
      return CurrentTrack;
    }
    if(ReceivingTrack){
      characters[word_counter] = receive;
      word_counter++;
      return "";
    }
  }
  return "";
}

void BluetoothModule::SetSensor(Sensor* sensor){
  MySensor = sensor;
}

String BluetoothModule::GetCurrentTrack(){
  return CurrentTrack;
}

void BluetoothModule::NextTrack(){
  Blue.write("N");
}

void BluetoothModule::PrevTrack(){
  Blue.write("P");
}

void BluetoothModule::VolUp(){
  Blue.write("U");
}

void BluetoothModule::VolDown(){
  Blue.write("D");
}

void BluetoothModule::DoneSettingVol(){
  MyDisplay->set_text(CurrentTrack);
}

void BluetoothModule::StopPlaying(){
  Blue.write("S");
}

