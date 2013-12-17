// select the pin from the encoder 4051N
int muxSelectA_pin = 32;      // S0
int muxSelectB_pin = 31;      // S1
int muxSelectC_pin = 30;      // S2
// led indicator of the select pin
int ledA_pin = 9;
int ledB_pin = 8;
int ledC_pin = 7;
// analog declaration
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
  
  delay(100);
  Serial.println("***********************");
  Serial.println("Start");
  Serial.println("Enter a number 0 and 7, inclusive");  
  Serial.println("***********************\n");
  
  // declare the ledPin as an OUTPUT:
  pinMode(ledA_pin, OUTPUT);
  pinMode(ledB_pin, OUTPUT);
  pinMode(ledC_pin, OUTPUT);
  pinMode(muxSelectA_pin, OUTPUT);
  pinMode(muxSelectB_pin, OUTPUT);  
  pinMode(muxSelectC_pin, OUTPUT);
  pinMode(sensorPin, INPUT);  
}

void loop() 
{
  while (Serial.available() > 0) 
  {
    int pinSelected = Serial.parseInt(); 
    
    //Output progress via Serial
    Serial.print("Pin Selected:");
    Serial.print(pinSelected);
    
    int ledA_value = 0;
    int ledB_value = 0;
    int ledC_value = 0;
    switch(pinSelected)
    {
      case 0:
        ledA_value = 0;
        ledB_value = 0;
        ledC_value = 0;
        break;
      case 1:
        ledA_value = 1;
        ledB_value = 0;
        ledC_value = 0;
        break;
      case 2:
        ledA_value = 0;
        ledB_value = 1;
        ledC_value = 0;
        break;
      case 3:
        ledA_value = 1;
        ledB_value = 1;
        ledC_value = 0;
        break;
      case 4:
        ledA_value = 0;
        ledB_value = 0;
        ledC_value = 1;
        break;
      case 5:
        ledA_value = 1;
        ledB_value = 0;
        ledC_value = 1;
        break;
      case 6:
        ledA_value = 0;
        ledB_value = 1;
        ledC_value = 1;
        break;
      case 7:
        ledA_value = 1;
        ledB_value = 1;
        ledC_value = 1;
        break;
      default:
        ledA_value = 0;
        ledB_value = 0;
        ledC_value = 0;
        break;
    }
    
    //Output to LED for inspection
    digitalWrite(ledA_pin, ledA_value);
    digitalWrite(ledB_pin, ledB_value);
    digitalWrite(ledC_pin, ledC_value);
    
    //Output to serial for inspection
    Serial.print(" (");
    Serial.print(ledC_value);
    Serial.print(" ");
    Serial.print(ledB_value);
    Serial.print(" ");    
    Serial.print(ledA_value);
    Serial.println(")");
    
    //Send command
    int value = read4051N(ledA_value, ledB_value, ledC_value); 
    
    //Wait
    Serial.print("Analog Value = ");
    Serial.println(value);
    delay(50);
  }                
}

int read4051N(int A, int B, int C)
{
  digitalWrite(muxSelectA_pin, A);
  digitalWrite(muxSelectB_pin, B);
  digitalWrite(muxSelectC_pin, C);  
  
  //Wait for the encoder to set
  delay(1);
  
  //Read Value
  return analogRead(sensorPin);
}
