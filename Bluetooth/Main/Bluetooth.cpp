#include "Bluetooth.h"

BluetoothModule::BluetoothModule(int RX,int TX) : Blue(RX,TX){
  Blue.begin(9600);
}

BluetoothModule::Update(){
  if(Blue.available() > 0) 
  {
    char receive = Blue.read(); //Read from Serial Communication
    Serial.println(receive);
    
  }
  Blue.write("Y");


}