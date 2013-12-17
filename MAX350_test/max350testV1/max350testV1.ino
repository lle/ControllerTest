/*
 Test code for MAX350 using Arduino MEGA

 Circuit:
 CS: 
 MOSI: pin 51
 MISO: pin 50
 SCK: pin 5
 
 */

// the sensor communicates using SPI, so include the library:
#include <SPI.h>

// pins used for the connection with the sensor
// the other you need are controlled by the SPI library):
const int chipSelectPin = 49;

void setup() {
  Serial.begin(9600);

  // start the SPI library:
  SPI.begin();

  // initalize the  data ready and chip select pins:
  pinMode(chipSelectPin, OUTPUT);

  // give the sensor time to set up:
  delay(100);
  Serial.println("***********************");
  Serial.println("Start");
  Serial.println("Enter a number between 0 and 7, inclusive");  
  Serial.println("***********************\n");
}

void loop() {
  while (Serial.available() > 0) 
  {
    int pinSelected = Serial.parseInt(); 
    
    //Output progress via Serial
    Serial.print("Pin Selected:");
    Serial.println(pinSelected);
    
    //Send command
    writeMAX350(pinSelected);    
    
    //Wait
    Serial.println(" ");
    delay(500);
  }
}

void writeMAX350(int outputSelect) 
{
  // take the chip select low to select the device:
  digitalWrite(chipSelectPin, LOW);
  
  //Generate Data
  byte byteSent = 0x00000001 << outputSelect;
  Serial.print("Sent data: ");
  Serial.println(byteSent, BIN);
  
  SPI.transfer(byteSent);  //Send value to record into register

  // take the chip select high to de-select:
  digitalWrite(chipSelectPin, HIGH);
}

