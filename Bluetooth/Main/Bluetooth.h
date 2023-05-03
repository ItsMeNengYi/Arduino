
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <SoftwareSerial.h> 

class Sensor;

class BluetoothModule {
  public:
    BluetoothModule(int RX,int TX);
  private:
    SoftwareSerial Blue;
    String CurrentTrack;
    Sensor* MySensor;
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
  private:

};

#endif