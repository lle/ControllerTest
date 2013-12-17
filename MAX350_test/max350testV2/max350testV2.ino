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
  Serial.println("Enter a number between 0 and 3, inclusive");  
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
    delay(100);
  }
}

void writeMAX350(int outputSelect) 
{
  //Generate Data
  byte byteSent = 0b00000000;
  switch (outputSelect)
  {
    case 0:
      byteSent = 0b10000001;  //NO0B and NO0A closed state 
      break;
    case 1:
      byteSent = 0b01000010;  //NO1B and NO1A closed state
      break;
    case 2:
      byteSent = 0b00100100;  //NO2B and NO2A closed state
      break;
    case 3:
      byteSent = 0b00011000;  //NO3B and NO3A closed state
      break;
    default:
      byteSent = 0b00000000;  //No output. All circuit are in open state
      break;
  }
  
  // take the chip select low to select the device:
  digitalWrite(chipSelectPin, LOW);
    
  Serial.print("Sent data: ");
  Serial.println(byteSent, BIN);
  
  SPI.transfer(byteSent);  //Send value to record into register

  // take the chip select high to de-select:
  digitalWrite(chipSelectPin, HIGH);
}

