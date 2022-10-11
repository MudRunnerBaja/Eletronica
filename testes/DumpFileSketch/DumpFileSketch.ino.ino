/*
  SD card file dump

  This example shows how to read a file from the SD card using the
  SD library and send it over the serial port.

  The circuit:
   SD card attached to SPI bus as follows:
   ** MISO - pin 0
   ** MOSI - pin 3
   ** CS   - pin 1
   ** SCK  - pin 2

  created  22 December 2010
  by Limor Fried
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>

pin_size_t RXPIN = 12; // MISO
pin_size_t CSPIN = 13;
pin_size_t SCKPIN = 10;
pin_size_t TXPIN = 11; // MOSI

const int chipSelect = 17;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.print("SOCORRO!!!!!!!!!!!");
  SPI1.setRX(RXPIN);
  SPI1.setTX(TXPIN);
  SPI1.setSCK(SCKPIN);
  SPI1.setCS(CSPIN);
  SPI1.begin(CSPIN);

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt");

  // if the file is available, write to it:
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}

void loop() {
}
