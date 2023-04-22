
#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include <Arduino.h>
#include <SoftwareSerial.h> 


class BluetoothModule {
  public:
    BluetoothModule(int RX,int TX);
  private:
    SoftwareSerial Blue;
  public:
    Update();
  public:
    void NextTrack();
    void PrevTrack();
    void VolUp();
    void VolDown();

};

#endif