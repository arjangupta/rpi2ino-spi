#include <SPI.h>

// SPI peripheral code used from 
// https://roboticsbackend.com/raspberry-pi-master-arduino-uno-slave-spi-communication-with-wiringpi/

void setup() {
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  // turn on interrupts
  SPI.attachInterrupt();

  // Print setup
  Serial.begin(9600);
}

// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;
  SPDR = c+10;
}  // end of interrupt service routine (ISR) for SPI

int print_counter = 0;

void loop () 
{
  if (print_counter == 25) {
    Serial.print("Running SPI Peripheral program.\n");
    print_counter = 0;
  }
  else {
    ++print_counter;
  }
  delay(200);
}