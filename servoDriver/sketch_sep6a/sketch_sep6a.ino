// #include <Servo.h>

// Servo myservo;  // Create a servo object to control a servo motor
// const int inputPin = 13;
// void setup() {
//   Serial.begin(9600);
//   pinMode(inputPin, INPUT);
//   myservo.attach(9);  // Attach the servo to pin 9 (you can use any digital pin)
// }

// void loop() {
//   //   Serial.println(digitalRead(inputPin));
//   // if(digitalRead(inputPin)==HIGH){
//   //   Serial.println(90);
//   //   moveServoToPosition(90); 
//   // }else{
//   //   Serial.println(135);
//   //   moveServoToPosition(135); 
//   // } 
  
//   Serial.println(135);
//   moveServoToPosition(135); 
//   delay(500);  // Wait for 2 seconds

// }

// void moveServoToPosition(int degrees) {
//   // Map degrees to the servo pulse width range
//   int pulseWidth = map(degrees, 0, 270, 544, 2400);
//   // DS3235
//   // int pulseWidth = map(degrees, 0, 270, 500, 2500);

//   // Set the servo position based on the pulse width
//   myservo.writeMicroseconds(pulseWidth);

// }
#include <Wire.h>

// Set I2C bus to use: Wire, Wire1, etc.
#define WIRE Wire

void setup() {
  WIRE.begin();

  Serial.begin(9600);
  while (!Serial)
     delay(10);
  Serial.println("\nI2C Scanner");
}


void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    WIRE.beginTransmission(address);
    error = WIRE.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
}