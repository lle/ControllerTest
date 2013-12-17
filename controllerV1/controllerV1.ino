/*
  Reading a serial ASCII-encoded string.
 
 This sketch demonstrates the Serial parseInt() function.
 It looks for an ASCII string of comma-separated values.
 It parses them into ints, and uses those to fade an RGB LED.
 
 Circuit: Common-anode RGB LED wired like so:
 * Red cathode: digital pin 3
 * Green cathode: digital pin 5
 * blue cathode: digital pin 6
 * anode: +5V
 
 created 13 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
 */

// pins for the LEDs:
const int led = 4;
const int mosfet = 5;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // make the pins outputs:
  pinMode(led, OUTPUT); 
  pinMode(mosfet, OUTPUT); 

  Serial.println("Start");
  Serial.println("Enter mode '0' or '1'");
}

void loop() {
  
  // if there's any serial available, read it:
  while (Serial.available() > 0) 
  {
    // look for the next valid integer in the incoming serial stream:
    int mode = Serial.parseInt(); 
    
    Serial.print("Data received = ");
    Serial.println(mode);
   
    if(mode == 1)
    {
       digitalWrite(led, HIGH);
       digitalWrite(mosfet, HIGH);
       Serial.println("MODE: ON");         
    }
    else
    {
       digitalWrite(led, LOW);
       digitalWrite(mosfet, LOW);
       Serial.println("MODE: OFF");
    }
  }
}








