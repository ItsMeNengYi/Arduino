
#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include <Arduino.h>
#include <SoftwareSerial.h> 


class BluetoothModule {
  public:
    BluetoothModule(int RX,int TX);
  private:
    SoftwareSerial Blue;
    String CurrentTrack;
  public:
    Update();
    String GetCurrentTrack();
  public:
    void NextTrack();
    void PrevTrack();
    void VolUp();
    void VolDown();
    void StopPlaying();

};

#endif