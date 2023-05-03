#include "Bluetooth.h"

/*
    "O" = default, none
    "N" = next track
    "P" = prev track
    "S" = pause track
    "V" = set volume
    "U" = volume up
    "D" = volume down
  */


BluetoothModule::BluetoothModule(int RX,int TX) : Blue(RX,TX){
  Blue.begin(9600);
  this->CurrentTrack = "None";
}

BluetoothModule::Update(){
  if(Blue.available() > 0) 
  {
    char receive = Blue.read(); //Read from Serial Communication
    CurrentTrack = receive;
    
  }
}

String BluetoothModule::GetCurrentTrack(){
  return CurrentTrack;
}

void BluetoothModule::NextTrack(){
  Blue.write("N");

}
void BluetoothModule::PrevTrack(){
  Blue.write("p");
}
void BluetoothModule::VolUp(){
  Blue.write("U");
}
void BluetoothModule::VolDown(){
  Blue.write("D");
}
void BluetoothModule::StopPlaying(){
  Blue.write("S");
}

