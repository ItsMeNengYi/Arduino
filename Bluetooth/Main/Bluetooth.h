
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <SoftwareSerial.h> 
#include "Display.h"

class Sensor;

class BluetoothModule {
  public:
    BluetoothModule(int RX,int TX,Display* display);
  private:
    String CurrentTrack;
    SoftwareSerial Blue;
    Sensor* MySensor;
    Display* MyDisplay;
    bool ReceivingTrack;
    short word_counter;
    short word_length;
    char characters[42];
  public:
    Update();
    void SetSensor(Sensor* sensor);
    void NextTrack();
    void PrevTrack();
    void VolUp();
    void VolDown();
    void StopPlaying();
    String GetCurrentTrack();
  private:

};

#endif