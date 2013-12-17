//pin configuration
int led = 13;
int input_pin = 14;
int clock_pin = 15;
int mode_pin = 16;
int delay_time = 1;

// the setup routine runs once when you press reset:
void setup() {                
  Serial.begin(9600);
  Serial.println("***********************");
  Serial.println("Start");
  Serial.println("Enter a number 0 and 7, inclusive");  
  Serial.println("***********************\n");
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  pinMode(input_pin, INPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(mode_pin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  //load all input to the LS165 latches
  digitalWrite(mode_pin, LOW);
  delay(delay_time);
  digitalWrite(mode_pin,HIGH);
  delay(delay_time);
  
  //start clocking to read the 8 bit recorded in the LS165
  for(int i=0; i<8; i++)
  {  
    //On rising edge, output value from input_pin
    Serial.print( digitalRead(input_pin) );
    delay(delay_time);
    
    //Clock once
    digitalWrite(clock_pin, LOW);
    delay(delay_time);
    digitalWrite(clock_pin, HIGH);
    delay(delay_time);
  }
  //done cycle
  Serial.println(" ");   
  delay(delay_time);
}
