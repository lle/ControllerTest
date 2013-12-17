
// Written by Nick Gammon
// February 2011

#include <SPI.h>
int ledpin = 13;

void setup (void)
{
  pinMode(ledpin, OUTPUT);
  
  Serial.begin (115200);   // debugging

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // now turn on interrupts
  SPI.attachInterrupt();

}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect)
{
  SPDR;  // grab byte from SPI Data Register
  Serial.println(SPDR);
}  
// end of interrupt routine SPI_STC_vect

// main loop - wait for flag set in interrupt routine
void loop (void)
{
  digitalWrite(ledpin, HIGH);
  delay(100);
  digitalWrite(ledpin,LOW);
  delay(100);    
}  // end of loop
