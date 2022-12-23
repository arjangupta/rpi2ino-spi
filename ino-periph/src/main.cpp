#include <SPI.h>

// SPI peripheral code used from 
// https://roboticsbackend.com/raspberry-pi-master-arduino-uno-slave-spi-communication-with-wiringpi/

namespace
{
  bool received_spi_data = false;
  byte spi_byte = 0x0;
  int print_counter = 0;
} // anonymous namespace

void setup() {
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  // turn on interrupts
  SPI.attachInterrupt();

  // Print setup
  Serial.begin(9600);

  // Initialize helper vars
  received_spi_data = false;
  spi_byte = 0x0;
  print_counter = 500;
}

// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;
  received_spi_data = true;
  spi_byte = c;
}  // end of interrupt service routine (ISR) for SPI


void loop () 
{
  if (print_counter == 500) {
    Serial.print("Running SPI Peripheral program.\n");
    print_counter = 0;
  }
  else {
    ++print_counter;
  }
  if (received_spi_data) {
    Serial.print("We received a byte over SPI: ");
    Serial.print(spi_byte, HEX); // print out byte in hex
    Serial.print("\n");
    // Reset flag
    received_spi_data = false;
  }
  delay(200);
}